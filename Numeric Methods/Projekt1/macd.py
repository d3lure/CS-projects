import math
import numpy as np
import pandas as pd
import plotly.subplots as ps
import plotly.graph_objects as go

pd.options.mode.chained_assignment = None


def ema(data, span):

    weight = 2 / (span + 1)
    ema = np.zeros(len(data))
    ema[0] = data[0]

    for i in range(1, len(data)):
        ema[i] = (data[i] * weight) + (ema[i - 1] * (1 - weight))

    return ema


def calculate_macd(data):

    fast = ema(data.Close, 12)
    slow = ema(data.Close, 26)

    macd = fast - slow

    signal = ema(macd, 9)

    trigger = macd - signal

    macd = pd.Series(macd)
    signal = pd.Series(signal)
    trigger = pd.Series(trigger)

    data['MACD'] = data.index.map(macd)
    data['SIGNAL'] = data.index.map(signal)
    data['Trigger'] = data.index.map(trigger)
    return data


def prepare_data(file_name, num_rows):
    data = pd.read_csv(file_name, nrows=num_rows)[::-1].reset_index(drop=True)

    try:
        data['Close'] = data['Close'].str.replace('$', '', regex=True)
        data['Open'] = data['Open'].str.replace('$', '', regex=True)
        data['High'] = data['High'].str.replace('$', '', regex=False)
        data['Low'] = data['Low'].str.replace('$', '', regex=True)

        data['Close'] = pd.to_numeric(data['Close'])
        data['Open'] = pd.to_numeric(data['Open'])
        data['High'] = pd.to_numeric(data['High'])
        data['Low'] = pd.to_numeric(data['Low'])
    except:
        pass

    calculate_macd(data)
    return data


def draw_plot(data, title, better=True):

    if better:
        fig = ps.make_subplots(rows=3, cols=1, vertical_spacing=0.05, shared_xaxes=True)
        fig.add_trace(go.Scatter(
            x=data.Date, y=data.RSI, name='RSI'
        ), row=3, col=1)

        fig.update_yaxes(range=[-10, 110], row=3, col=1)
        fig.add_hline(y=40, col=1, row=3, line_color='#336699', line_width=2, line_dash='dash')
        fig.add_hline(y=60, col=1, row=3, line_color='#336699', line_width=2, line_dash='dash')

        fig.update_layout(
            xaxis3_rangeslider_visible=False,
            yaxis3=dict(
                title="RSI Value"
            ),
        )
    else:
        fig = ps.make_subplots(rows=2, cols=1, vertical_spacing=0.05, shared_xaxes=True)

    fig.add_trace(go.Candlestick(
        x=data.Date, open=data.Open, high=data.High,
        low=data.Low, close=data.Close, name=title
    ), row=1, col=1)

    fig.add_trace(go.Scatter(x=data.Date, y=data.MACD, mode='lines', name='MACD'), row=2, col=1)
    fig.add_trace(go.Scatter(x=data.Date, y=data.SIGNAL, mode='lines', name='SIGNAL'), row=2, col=1)

    fig.add_trace(go.Scatter(
        mode="markers", x=data.Date, y=data.Buy, marker_symbol="triangle-up",
        marker_color="darkgreen", marker_line_width=0, marker_size=12, name="Buy Signal"
    ), row=1, col=1)

    fig.add_trace(go.Scatter(
        mode="markers", x=data.Date, y=data.Sell, marker_symbol="triangle-down",
        marker_color="darkred", marker_line_width=0, marker_size=12, name="Sell Signal"
    ), row=1, col=1)

    fig.update_layout(
        xaxis_rangeslider_visible=False,
        xaxis2_rangeslider_visible=not better,

        legend=dict(
            yanchor="top", y=1,
            xanchor="right", x=1.1
        ),
        yaxis=dict(
            title="Value [$]"
        ),
        yaxis2=dict(
            title="MACD Value"
        ),

    )
    fig.show()


def macd_algorithm(data, num_of_stocks=1000, better=True):

    data['Buy'], data['Sell'] = None, None
    data_diff = pd.Series(np.diff(data['Close'])).fillna(0)

    # Implementation of RSI (Relative Strength Index)
    window_length = 0
    if better:
        window_length = 14
        prev_avg_gain, prev_avg_loss = None, None
        avg_gain, avg_loss = None, None
        data_gains = pd.Series(data_diff.clip(lower=0).fillna(0))
        data_losses = pd.Series(data_diff.clip(upper=0).abs().fillna(0))
        rsi_values = []

        for i in range(len(data_diff)):
            if i == window_length:
                avg_gain = data_gains.iloc[0:window_length-1].sum() / window_length
                avg_loss = data_losses.iloc[0:window_length-1].sum() / window_length
            elif i > window_length:
                avg_gain = (prev_avg_gain * (window_length - 1) + data_gains[i]) / window_length
                avg_loss = (prev_avg_loss * (window_length - 1) + data_losses[i]) / window_length

            prev_avg_gain = avg_gain
            prev_avg_loss = avg_loss

            if avg_gain is not None:
                rs = avg_gain / avg_loss
                rsi = 100 - (100 / (1 + rs))
                rsi_values.append(rsi)
            else:
                rsi_values.append(None)

        data['RSI'] = pd.Series(rsi_values)

    # Add buy/sell indicators from MACD
    last_trig = None
    for i in range(len(data)):
        curr_trig = data.Trigger[i]
        if last_trig is not None:
            if last_trig < 0 and curr_trig > 0:
                data['Buy'][i] = data['Close'][i]
            if last_trig > 0 and curr_trig < 0:
                data['Sell'][i] = data['Close'][i]

        last_trig = curr_trig

    if better:
        for i in range(window_length, len(data)):
            if data['RSI'][i] > 55 and data['Buy'][i] is not None:
                pass
            elif data['RSI'][i] < 45 and data['Sell'][i] is not None:
                pass
            else:
                data['Buy'][i] = None
                data['Sell'][i] = None

    # Check whether we bought or sold stocks
    # throughout data, based on previously added indicators
    owned = [0] * len(data)
    for i in range(len(data)):
        if data.Buy[i] is not None:
            owned[i] = 1
        elif data.Sell[i] is not None:
            owned[i] = 0
        else:
            owned[i] = owned[i-1]

    profit = 0
    for i in range(len(data_diff)):
        try:
            tmp_profit = data_diff[i] * owned[i] * num_of_stocks
            profit += tmp_profit
        except:
            print("Error")

    start_value = num_of_stocks * data['Close'][0]
    profit_percent = math.floor((profit / start_value) * 100)

    print('Starting value of {} stocks: {}$'.format(num_of_stocks, round(start_value, 2)))
    print('Profit after {} market days: {}$ ({}% of starting value)'.format(len(data), round(profit, 2), profit_percent))


def show_results(data_path, title, num_days=1000, macd_rsi=True):
    data = prepare_data(data_path, num_days)
    macd_algorithm(data, better=macd_rsi)
    draw_plot(data, title, better=macd_rsi)


show_results('assets/tesla_data.csv', 'Name', macd_rsi=False)
