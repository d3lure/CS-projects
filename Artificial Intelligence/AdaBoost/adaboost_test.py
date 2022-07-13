import pickle
import time, os, random
import numpy as np
import tensorflow as tf
from tensorflow import keras
import matplotlib.pyplot as plt

model = pickle.load(open('adb_model2.sav', 'rb'))

# model = keras.models.load_model('adb_model2.sav')
img_height, img_width = 80, 80
img_dir = "../imgs/" + random.choice(os.listdir("../imgs/"))
img = tf.keras.utils.load_img(img_dir, target_size=(img_height, img_width))
plt.imshow(img)

img_array = tf.keras.utils.img_to_array(img)
# img_array = tf.expand_dims(img_array, 0)

img_array.reshape((1, 80 * 80 * 3))
print(img_array.shape)

res = model.predict(img_array)
print(res)
