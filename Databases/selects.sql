USE [BD-laby]

-- Które z lotów by³y najbardziej op³acalne dla
-- klienta? Op³acalne, czyli móg³ przebyæ mo¿liwie najd³u¿sz¹ podró¿ za mo¿liwie
-- najni¿sz¹ cenê. D³ugoœæ podró¿y liczona jest przez czas spêdzony w rakiecie(od
-- wylotu do przylotu). Wyniki uporz¹dkuj rosn¹co.
--SELECT * FROM (
--	SELECT DATEDIFF(day, Planowany_czas_odlotu, Planowany_czas_przylotu) AS Diff,
--	Cena,
--	Nr_lotu,
--	Nazwa_destynacji
--FROM Loty) AS Wynik ORDER BY Wynik.Cena/Wynik.Diff ASC -- ratio


-- Uporz¹dkuj planety (malej¹co) wed³ug ich popularnoœci. 
-- Policz liczbê lotów, których celem by³y poszczególne planety.
--SELECT Nazwa_destynacji, COUNT(Nazwa_destynacji) AS Ilosc_lotow
--FROM Loty
--GROUP BY Nazwa_destynacji ORDER BY Ilosc_lotow DESC


-- Uporz¹dkuj planety (malej¹co) wed³ug ich popularnoœci. 
-- Policz liczbê osób, które polecia³y na poszczególne planety.
--SELECT Nazwa_destynacji, COUNT(Nazwa_destynacji) AS Suma FROM Pasazerowie, Loty 
--WHERE Loty.Nr_lotu=Pasazerowie.Numer_lotu 
--GROUP BY Nazwa_destynacji ORDER BY Suma DESC


-- Zrób ranking 5 najwy¿ej ocenianych planet
-- bior¹c pod uwagê oceny wszystkich pasa¿erów
--SELECT TOP 5 Nazwa_ciala, AVG(Wartosc) AS Ocena FROM Oceny 
--WHERE Nazwa_ciala IN (SELECT Nazwa_planety FROM Planety)
--GROUP BY Nazwa_ciala ORDER BY Ocena DESC


-- Wyœwietl planety, które maj¹ ksiê¿yce i wyœwietl ich dane obok siebie
--SELECT * FROM Ksiezyce INNER JOIN Planety ON Nazwa_pl = Nazwa_planety ORDER BY Nazwa_pl


-- Podaj œredni¹ wieku pasazerów ze wzglêdu na nazwê destynacji 
-- (w celu targetowania niektórych planet dla innych grup wiekowych)
--SELECT DISTINCT Loty.Nazwa_destynacji, AVG(Pasazerowie.Wiek) AS Sredni_wiek 
--FROM Loty, Pasazerowie WHERE Loty.Nr_lotu = Pasazerowie.Numer_lotu
--GROUP BY Nazwa_destynacji


-- Podaj œrednie temperatury (w Celsjuszach) ze wzglêdu na typ planety
--GO
--CREATE VIEW TYPY_TEMP AS
--SELECT Typ, (AVG(Temperatura)-273) AS Srednia_temp FROM Planety, Ciala_Niebieskie WHERE Ciala_Niebieskie.Nazwa=Planety.Nazwa_planety
--GROUP BY Typ

--GO
--SELECT * FROM TYPY_TEMP
--DROP VIEW TYPY_TEMP


-- Podaj wszystkie informacje na temat lotów pasa¿erów, informacji o locie, po informacje o destynacji
--SELECT * FROM Pasazerowie INNER JOIN Loty ON Nr_lotu=Numer_lotu 
--LEFT JOIN Planety ON Nazwa_planety = Nazwa_destynacji LEFT JOIN Ciala_Niebieskie ON Nazwa = Nazwa_destynacji
