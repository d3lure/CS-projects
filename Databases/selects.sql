USE [BD-laby]

-- Kt�re z lot�w by�y najbardziej op�acalne dla
-- klienta? Op�acalne, czyli m�g� przeby� mo�liwie najd�u�sz� podr� za mo�liwie
-- najni�sz� cen�. D�ugo�� podr�y liczona jest przez czas sp�dzony w rakiecie(od
-- wylotu do przylotu). Wyniki uporz�dkuj rosn�co.
--SELECT * FROM (
--	SELECT DATEDIFF(day, Planowany_czas_odlotu, Planowany_czas_przylotu) AS Diff,
--	Cena,
--	Nr_lotu,
--	Nazwa_destynacji
--FROM Loty) AS Wynik ORDER BY Wynik.Cena/Wynik.Diff ASC -- ratio


-- Uporz�dkuj planety (malej�co) wed�ug ich popularno�ci. 
-- Policz liczb� lot�w, kt�rych celem by�y poszczeg�lne planety.
--SELECT Nazwa_destynacji, COUNT(Nazwa_destynacji) AS Ilosc_lotow
--FROM Loty
--GROUP BY Nazwa_destynacji ORDER BY Ilosc_lotow DESC


-- Uporz�dkuj planety (malej�co) wed�ug ich popularno�ci. 
-- Policz liczb� os�b, kt�re polecia�y na poszczeg�lne planety.
--SELECT Nazwa_destynacji, COUNT(Nazwa_destynacji) AS Suma FROM Pasazerowie, Loty 
--WHERE Loty.Nr_lotu=Pasazerowie.Numer_lotu 
--GROUP BY Nazwa_destynacji ORDER BY Suma DESC


-- Zr�b ranking 5 najwy�ej ocenianych planet
-- bior�c pod uwag� oceny wszystkich pasa�er�w
--SELECT TOP 5 Nazwa_ciala, AVG(Wartosc) AS Ocena FROM Oceny 
--WHERE Nazwa_ciala IN (SELECT Nazwa_planety FROM Planety)
--GROUP BY Nazwa_ciala ORDER BY Ocena DESC


-- Wy�wietl planety, kt�re maj� ksi�yce i wy�wietl ich dane obok siebie
--SELECT * FROM Ksiezyce INNER JOIN Planety ON Nazwa_pl = Nazwa_planety ORDER BY Nazwa_pl


-- Podaj �redni� wieku pasazer�w ze wzgl�du na nazw� destynacji 
-- (w celu targetowania niekt�rych planet dla innych grup wiekowych)
--SELECT DISTINCT Loty.Nazwa_destynacji, AVG(Pasazerowie.Wiek) AS Sredni_wiek 
--FROM Loty, Pasazerowie WHERE Loty.Nr_lotu = Pasazerowie.Numer_lotu
--GROUP BY Nazwa_destynacji


-- Podaj �rednie temperatury (w Celsjuszach) ze wzgl�du na typ planety
--GO
--CREATE VIEW TYPY_TEMP AS
--SELECT Typ, (AVG(Temperatura)-273) AS Srednia_temp FROM Planety, Ciala_Niebieskie WHERE Ciala_Niebieskie.Nazwa=Planety.Nazwa_planety
--GROUP BY Typ

--GO
--SELECT * FROM TYPY_TEMP
--DROP VIEW TYPY_TEMP


-- Podaj wszystkie informacje na temat lot�w pasa�er�w, informacji o locie, po informacje o destynacji
--SELECT * FROM Pasazerowie INNER JOIN Loty ON Nr_lotu=Numer_lotu 
--LEFT JOIN Planety ON Nazwa_planety = Nazwa_destynacji LEFT JOIN Ciala_Niebieskie ON Nazwa = Nazwa_destynacji
