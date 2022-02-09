USE [BD-laby]

DROP TABLE Oceny
DROP TABLE Pasazerowie
DROP TABLE Statki
DROP TABLE Loty
DROP TABLE Ksiezyce
DROP TABLE Planety
DROP TABLE Gwiazdy
DROP TABLE Galaktyki
DROP TABLE Konstelacje
DROP TABLE Ciala_Niebieskie

SELECT * FROM Planety
SELECT * FROM Ksiezyce
SELECT * FROM Gwiazdy
SELECT * FROM Galaktyki
SELECT * FROM Konstelacje
SELECT * FROM Ciala_Niebieskie
SELECT * FROM Loty
SELECT * FROM Oceny
SELECT * FROM Pasazerowie


INSERT INTO Konstelacje
VALUES 
	('Andromeda', 'Alpheratz'),
	('Baran', 'Hamal'),
	('Byk', 'Aldebaran'),
	('Erydan', 'Achernar'),
	('Feniks', 'Ankaa'),
	('Go³¹b', 'Alfa Columbae'),
	('Malarz', 'Alfa Pictoris'),
	('Orion', 'Rigel'),
	('Perseusz', 'Mirfak'),
	('Piec', 'Alfa Fornacis'),
	('Ryby', 'Eta Piscium'),
	('Rylec', 'Alfa Caeli'),
	('RzeŸbiarz', 'Alfa Sculptoris'),
	('Trójk¹t', 'Beta Trianguli'),
	('WoŸnica', 'Kapella'),
	('Zaj¹c', 'Arneb'),
	('Zegar', 'Alfa Horologii'),
	('Wieloryb', 'Diphda'),
	('Z³ota Ryba', 'Alfa Doradus'),
	('Pompa', 'Alfa Ant'),
	('Kruk', 'Gienah'),
	('Smok', 'Eltanin'),
	('Centaur', 'Alfa Centauri'),
	('Strzelec', 'Kaus Australis'),
	('Panna', 'Spica'),
	('Wielki Pies', 'Syriusz'),
	('Kil', 'Kanopus'),
	('Wolarz', 'Arktur'),
	('Lutnia', 'Wega'),
	('Ma³y Pies', 'Procjon'),
	('Lew', 'Regulus'),
	('Wielka NiedŸwiedzica', 'Alioth'),
	('Ryba Po³udniowa', 'Fomalhaut')

INSERT INTO Galaktyki
VALUES 
	('Wolf-Lundmark-Melotte', 8000, 'Nieregularna', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Wieloryb') ),
	('Messier 110', 17000, 'Eliptyczna', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Andromeda')),
	('Messier 32', 8000, 'Eliptyczna', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Andromeda')),
	('Andromeda', 195000, 'Spiralna', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Andromeda')),
	('Wielki Ob³ok Magellana', 30000, 'Nieregularna', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Z³ota Ryba')),
	('Karze³ Pompy', 5000, 'Eliptyczna', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Pompa')),
	('Droga Mleczna', 100000, 'Spiralna', NULL),
	('Arp 244', 500000, 'Nieregularna', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Kruk')),
	('NGC 5866', 60000, 'Soczewkowata', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Smok')),
	('NGC 5128', 60000, 'Soczewkowata', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Centaur')),
	('SagDEG', 10000, 'Eliptyczna', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Strzelec')),
	('GR 8', 1500, 'Nieregularna', (SELECT Nazwa FROM Konstelacje WHERE Nazwa='Panna'))

INSERT INTO Ciala_Niebieskie
VALUES
	('Syriusz A', 2.12, 9880, 1.75),
	('Kanopus', 8.50, 7280, 71.4),
	('Arktur', 1.08, 4286, 25.4),
	('Alfa Centauri A', 1.14, 5900, 1.1),
	('Wega', 2.15, 9660, 2.726),
	('Rigel', 23.0, 12100, 78.9),
	('Procjon', 1.42, 6530, 2.1),
	('Achernar', 7.0, 16900, 11.6),
	('Betelgeza', 18.0, 3500, 887.0),
	('Kapella', 2.573, 4920, 11.87),
	('Proxima Centauri', 0.122, 3042, 0.154),
	('Wolf 359', 0.09, 2800, 0.16),
	('Lalande 21185', 0.390, 3601, 0.392),
	('Lacaille 9352', 0.486, 3692, 0.470),
	('Tau Ceti', 0.783, 5344, 0.793),
	('S³oñce', 1.0, 5778, 1.0),

	('Merkury', 0.055, 442, 0.383),
	('Wenus', 0.815, 737, 0.950),
	('Ziemia', 1.0, 288, 1.0),
	('Mars', 0.107, 210, 0.532),
	('Jowisz', 317.83, 165, 11.209),
	('Saturn', 95.16, 134, 9.140),
	('Uran', 14.54, 76, 3.981),
	('Neptun', 17.15, 72, 3.865),
	('Proxima Centauri b', 1.27, 234, 1.30),
	('Proxima Centauri c', 7.0, 39, NULL),
	('Wolf 359 b', 43.90, NULL, NULL),
	('Wolf 359 c', 3.80, NULL, NULL),
	('Lacaille 9352 c', 7.6, 352, NULL),
	('Lalande 21185 b', 2.64, 370, NULL),

	('Ksiê¿yc', 0.0123, 250, 0.2727),
	('Fobos', 0.00000000179 , 233, 0.00177),
	('Deimos', 0.000000000247, 233, 0.000973),
	('Europa', 0.008, 102, 0.245),
	('Ganimedes', 0.025, 110, 0.413),
	('Io', 0.015, 110, 0.286),
	('Kallisto', 0.018, 134, 0.378),
	('Tytan', 0.0225, 94, 0.404),
	('Enceladus', 0.00018, 75, 0.0395),
	('Tryton', 0.00359, 38, 0.2122)

INSERT INTO Gwiazdy
VALUES
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Syriusz A'), 'A1V', 0.36, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Wielki Pies')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Kanopus'), 'A9 II', -0.11, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Kil')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Arktur'), 'K0 III', -0.52, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Wolarz')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Alfa Centauri A'), 'G2 V', 0.18, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Centaur')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Wega'), 'A0 Va', -0.56, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Lutnia')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Rigel'), 'B8 Ia', -0.06, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Orion')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Procjon'), 'F5 IV-V', -0.02, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Ma³y Pies')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Achernar'), 'B6 Vpe', NULL, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Erydan')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Betelgeza'), 'M1-2-Ia-Iab', 0.09, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Orion')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Kapella'), 'G8 III', -0.27, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'WoŸnica')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Proxima Centauri'), 'M5.5Ve', 0.21, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Centaur')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Wolf 359'), 'M6.5 Ve', 0.18, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Lew')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Lalande 21185'), 'M2V', -0.09, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Wielka NiedŸwiedzica')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Lacaille 9352'), 'M0.5V', -0.22, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Ryba Po³udniowa')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Tau Ceti'), 'G8V', -0.55, (SELECT Nazwa FROM Konstelacje WHERE Nazwa = 'Wieloryb')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'S³oñce'), 'G2 V', -0.55, NULL)

INSERT INTO Planety
VALUES
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Merkury'), 'Skalista', 0.240846, 0.387, 3.7, 0, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'S³oñce')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Wenus'), 'Skalista', 0.615198, 0.723, 8.87, 0, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'S³oñce')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Ziemia'), 'Skalista', 1.0, 1.0, 9.806, 0, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'S³oñce')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Mars'), 'Skalista', 1.880, 1.523, 3.72, 0, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'S³oñce')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Jowisz'), 'Gazowy Olbrzym', 11.862, 5.20, 24.79, 1, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'S³oñce')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Saturn'), 'Gazowy Olbrzym', 29.4571, 9.5826, 10.44, 1, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'S³oñce')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Uran'), 'Lodowy Olbrzym', 84.02, 19.191, 8.69, 1, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'S³oñce')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Neptun'), 'Lodowy Olbrzym', 164.8, 30.07, 11.15, 1, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'S³oñce')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Proxima Centauri b'), 'Skalista', 0.0306, 0.0485, NULL, 0, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'Proxima Centauri')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Proxima Centauri c'), 'Skalista', 5.282, 1.489, NULL, 0, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'Proxima Centauri')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Wolf 359 b'), 'Skalista', 0.007, 0.018, NULL, 0, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'Wolf 359')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Wolf 359 c'), 'Skalista', 8.04, 1.845, NULL, 0, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'Wolf 359')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Lacaille 9352 c'), 'Skalista', 0.05969, 0.120, NULL, 0, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'Lacaille 9352')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Lalande 21185 b'), 'Skalista', 0.0354, 0.0788, NULL, 0, (SELECT Nazwa_gwiazdy FROM Gwiazdy WHERE Nazwa_gwiazdy = 'Lalande 21185'))

INSERT INTO Ksiezyce
VALUES
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Ksiê¿yc'), 29.53, 384403, 1.622, (SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Ziemia')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Fobos'), 0.3189, 9376, 0.0057, (SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Mars')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Deimos'), 1.263, 23463, 0.003, (SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Mars')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Europa'), 3.551, 670900, 1.314, (SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Jowisz')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Ganimedes'), 7.154, 1070400, 1.428, (SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Jowisz')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Io'), 1.769, 421700, 1.796, (SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Jowisz')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Kallisto'), 16.689, 1882700, 1.235, (SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Jowisz')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Tytan'), 15.945, 1221870, 1.352, (SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Saturn')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Enceladus'), 1.370, 237948, 0.113, (SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Saturn')),
	((SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Tryton'), 5.877, 354759, 0.779, (SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Neptun'))

INSERT INTO Loty
VALUES
	((SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Mars'), '20220101', '20220115', '20220208', 1090),
	((SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Saturn'), '20220107', '20220129', '20220218', 2200),
	((SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Proxima Centauri b'), '20220204', '20220228', '20220317', 3999),
	((SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Wenus'), '20220404', '20220411', '20220430', 510),
	((SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Uran'), '20220411', '20220501', '20220522', 2340),
	((SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Proxima Centauri c'), '20220506', '20220605', '20220707', 3999),
	((SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Neptun'), '20220603', '20220619', '20220726', 1090),
	((SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Saturn'), '20220720', '20220805', '20220829', 2320),
	((SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Proxima Centauri b'), '20220909', '20221001', '20221102', 3589),
	((SELECT Nazwa_planety FROM Planety WHERE Nazwa_planety = 'Mars'), '20221113', '20221123', '20221208', 999)

INSERT INTO Pasazerowie
VALUES
	('Abigale', 'Gross', 76, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 1)),
	('Primrose', 'Mclaughlin', 34, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 1)),
	('Zayden', 'Grimes', 80, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 1)),
	('Aislinn', 'Brewer', 70, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 1)),
	('Dionne', 'Kirk', 30, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 2)),
	('Linda', 'Ridley', 28, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 2)),
	('Peter', 'Wolfe', 67, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 3)),
	('Heidi', 'Harrell', 48, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 2)),
	('Roxanne', 'Bradley', 46, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 1)),
	('Luqman', 'Berry', 25, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 3)),
	('Areeb', 'Sutton', 51, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 2)),
	('Kester', 'Herbert', 33, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 3)),
	('Sheridan', 'Warner', 22, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 2)),
	('John', 'Warners', 26, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 10))

INSERT INTO Statki
VALUES
	('ST-I', 10, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 1)),
	('SM-I', 100, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 2)),
	('SB-I', 1000, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 3)),
	('ST-I', 10, (SELECT Nr_lotu FROM Loty WHERE Nr_lotu = 10)),
	('SM-I', 100, NULL),
	('ST-I', 10, NULL),
	('SM-I', 100, NULL),
	('ST-I', 10, NULL),
	('SM-I', 100, NULL),
	('SB-I', 1000, NULL)

INSERT INTO Oceny
VALUES
	(57, (SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Wenus'), (SELECT ID From Pasazerowie WHERE ID = 1)),
	(14, (SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Merkury'), (SELECT ID From Pasazerowie WHERE ID = 1)),
	(77, (SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Mars'), (SELECT ID From Pasazerowie WHERE ID = 3)),
	(86, (SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Ziemia'), (SELECT ID From Pasazerowie WHERE ID = 5)),
	(25, (SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Proxima Centauri c'), (SELECT ID From Pasazerowie WHERE ID = 7)),
	(99, (SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Ziemia'), (SELECT ID From Pasazerowie WHERE ID = 3)),
	(12, (SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'S³oñce'), (SELECT ID From Pasazerowie WHERE ID = 7)),
	(57, (SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Proxima Centauri b'), (SELECT ID From Pasazerowie WHERE ID = 5)),
	(79, (SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Tytan'), (SELECT ID From Pasazerowie WHERE ID = 3)),
	(83, (SELECT Nazwa FROM Ciala_Niebieskie WHERE Nazwa = 'Saturn'), (SELECT ID From Pasazerowie WHERE ID = 8))


