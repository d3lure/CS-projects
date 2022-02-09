USE [BD-laby]

CREATE TABLE Ciala_Niebieskie (
	Nazwa VARCHAR(20) PRIMARY KEY, 
	Masa DOUBLE PRECISION CHECK(Masa > 0), /* wyra¿ona w masach S³oñca lub masach Ziemi */ 
	Temperatura INT CHECK(Temperatura >= 0), /* w Kelvinach */
	Promien DOUBLE PRECISION CHECK(Promien > 0), /* wyra¿ony w promieniach S³oñca lub Ziemi */
);

CREATE TABLE Konstelacje (
	Nazwa VARCHAR(20) PRIMARY KEY, 
	Najjasniejsza_gwiazda VARCHAR(20) NOT NULL, 
);

CREATE TABLE Galaktyki (
	Nazwa VARCHAR(32) PRIMARY KEY, 
	Srednica INT CHECK(Srednica > 0), -- light years
	Rodzaj VARCHAR(12) NOT NULL 
	CHECK (Rodzaj IN ('Spiralna', 'Soczewkowata' , 'Eliptyczna' , 'Nieregularna')) DEFAULT 'Nieregularna', /* tablica rodzajów */
	Nazwa_konst VARCHAR(20) DEFAULT NULL REFERENCES Konstelacje
);

CREATE TABLE Gwiazdy (
	Nazwa_gwiazdy VARCHAR(20) PRIMARY KEY REFERENCES Ciala_Niebieskie ON DELETE CASCADE,

	Typ_widmowy VARCHAR(16), 
	Metalicznosc FLOAT,
	Nazwa_konstelacji VARCHAR(20) DEFAULT NULL REFERENCES Konstelacje,
);

CREATE TABLE Planety (
	Nazwa_planety VARCHAR(20) PRIMARY KEY REFERENCES Ciala_Niebieskie ON UPDATE CASCADE,

	Typ VARCHAR(16) CHECK (Typ IN ('Skalista', 'Gazowy Olbrzym', 'Lodowy Olbrzym')) DEFAULT 'Skalista',
	Okres_obiegu DOUBLE PRECISION CHECK(Okres_obiegu > 0), /* Julian year */
	Promien_orbity DOUBLE PRECISION CHECK(Promien_orbity > 0), -- w AU
	Przyspieszenie_g FLOAT CHECK(Przyspieszenie_g > 0), 
	Posiada_pierscien BIT DEFAULT 0, 
	
	Nazwa_gw VARCHAR(20) REFERENCES Gwiazdy ON DELETE CASCADE,
);

CREATE TABLE Ksiezyce (
	Nazwa_ksiezyca VARCHAR(20) PRIMARY KEY REFERENCES Ciala_Niebieskie,
	Okres_obiegu DOUBLE PRECISION CHECK(Okres_obiegu > 0),  -- w dniach ziemskich
	Promien_orbity INT CHECK(Promien_orbity > 0), -- w km
	Przyspieszenie_g FLOAT CHECK(Przyspieszenie_g > 0),
	Nazwa_pl VARCHAR(20) REFERENCES Planety ON UPDATE CASCADE,
);

CREATE TABLE Loty (
	Nr_lotu INT IDENTITY(1,1) PRIMARY KEY,
	Nazwa_destynacji VARCHAR(20) NOT NULL REFERENCES Planety ON DELETE CASCADE ON UPDATE CASCADE,
	Planowany_czas_odlotu DATE,
	Planowany_czas_przylotu DATE ,
	Planowany_czas_powrotu DATE, 
	Cena INT CHECK(Cena > 0),

	CHECK(Planowany_czas_przylotu > Planowany_czas_odlotu),
	CHECK(Planowany_czas_powrotu > Planowany_czas_przylotu),
);

CREATE TABLE Pasazerowie (
	ID INT IDENTITY(1,1) PRIMARY KEY, 
	Imie VARCHAR(16) NOT NULL CHECK (Imie NOT LIKE '%[^A-Z]%'),
	Nazwisko VARCHAR(32) NOT NULL CHECK (Nazwisko NOT LIKE '%[^A-Z]%'),
	Wiek INT NOT NULL CHECK(Wiek > 0),
	Numer_lotu INT REFERENCES Loty,
);

CREATE TABLE Statki (
	ID INT IDENTITY(1,1) PRIMARY KEY,
	Model VARCHAR(10) CHECK (Model IN ('ST-I', 'SM-I', 'SB-I')),
	Ilosc_miejsc INT CHECK(Ilosc_miejsc >= 10 AND Ilosc_miejsc <= 1000),   /* 10 - 1000 */
	Numer_lotu INT REFERENCES Loty, 
);

CREATE TABLE Oceny (
	ID INT IDENTITY(1,1) PRIMARY KEY,
	Wartosc INT CHECK(Wartosc >= 0 AND Wartosc <= 100), /* 0 - 100 */

	Nazwa_ciala VARCHAR(20) REFERENCES Ciala_Niebieskie ON DELETE CASCADE ON UPDATE CASCADE,
	Oceniajacy INT REFERENCES Pasazerowie
);

