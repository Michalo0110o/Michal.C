#Zad1.


CREATE TABLE pracownik (
    id_pracownika INT AUTO_INCREMENT PRIMARY KEY,
    imie VARCHAR(40) NOT NULL,
    nazwisko VARCHAR(60) NOT NULL,
    data_urodzenia DATE NOT NULL
);
 

INSERT INTO pracownik (imie, nazwisko, data_urodzenia) VALUES
('Norbert', 'Gierczak', '1990-05-15'),
('Kamil', 'Kowalenko', '1995-08-22'),
('Dawid', 'Jasper', '1988-12-01');
 

UPDATE pracownik
SET data_urodzenia = '1991-05-15'
WHERE id_pracownika = 1;


#Zad2.


CREATE TABLE zadanie (
    id_zadania INT AUTO_INCREMENT PRIMARY KEY,
    nazwa_zadania VARCHAR(150) NOT NULL,
    priorytet ENUM('normalny', 'wysoki', 'niski'),
    opis TEXT NULL,
    pracownik INT NULL,
    CONSTRAINT fk_zadanie_pracownik FOREIGN KEY (pracownik)
        REFERENCES pracownik(id_pracownika)
        ON DELETE SET NULL
);
 

ALTER TABLE zadanie
MODIFY COLUMN priorytet ENUM('normalny', 'wysoki', 'niski') DEFAULT 'normalny';
 

INSERT INTO zadanie (nazwa_zadania, priorytet, opis, pracownik) VALUES
('Przygotowanie raportu', 'wysoki', 'Szczegółowy raport finansowy', 1),
('Projekt bazy danych', 'normalny', 'Opracowanie diagramu ERD', 2),
('Testowanie modułu', 'niski', 'Testy jednostkowe kodu', 3);


#zad3.


CREATE TABLE projekt (
    id_projektu INT AUTO_INCREMENT PRIMARY KEY,
    nazwa_projektu VARCHAR(150) NOT NULL,
    data_rozpoczecia DATE NOT NULL,
    data_zakonczenia DATE NULL
);
 

ALTER TABLE projekt
ADD COLUMN menadzer_projektu INT NULL,
ADD CONSTRAINT fk_projekt_menadzer FOREIGN KEY (menadzer_projektu)
    REFERENCES pracownik(id_pracownika);
 

INSERT INTO projekt (nazwa_projektu, data_rozpoczecia, data_zakonczenia, menadzer_projektu) VALUES
('Wdrożenie CRM', '2025-01-10', '2025-06-30', 1),
('Aplikacja Mobilna', '2025-02-01', NULL, 2);
 

ALTER TABLE zadanie
ADD COLUMN projekt INT NULL,
ADD CONSTRAINT fk_zadanie_projekt FOREIGN KEY (projekt)
    REFERENCES projekt(id_projektu)
    ON DELETE CASCADE;
 

UPDATE zadanie SET projekt = 1 WHERE id_zadania IN (1, 2);
UPDATE zadanie SET projekt = 2 WHERE id_zadania = 3;

#zad4.


CREATE TABLE sprint (
    id_sprintu INT AUTO_INCREMENT PRIMARY KEY,
    numer_sprintu INT UNSIGNED NOT NULL,
    data_rozpoczecia DATE NOT NULL,
    data_zakonczenia DATE NOT NULL
);
 

ALTER TABLE zadanie
ADD COLUMN sprint INT NULL,
ADD CONSTRAINT fk_zadanie_sprint FOREIGN KEY (sprint)
    REFERENCES sprint(id_sprintu)
    ON DELETE SET NULL;
 

INSERT INTO sprint (numer_sprintu, data_rozpoczecia, data_zakonczenia) VALUES
(1, '2025-03-01', '2025-03-14');
 
UPDATE zadanie
SET sprint = 1
WHERE id_zadania IN (1, 2);


#Zad5.


CREATE TABLE status (
    id_statusu INT AUTO_INCREMENT PRIMARY KEY,
    nazwa_statusu VARCHAR(20) NOT NULL
);
 

INSERT INTO status (nazwa_statusu) VALUES
('Nowe'),
('W trakcie'),
('Zakończone');
 

CREATE TABLE zadanie_has_status (
    id_zdarzenia INT AUTO_INCREMENT PRIMARY KEY,
    id_zadania INT NOT NULL,
    id_statusu INT NOT NULL,
    data_zdarzenia TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_zhs_zadanie FOREIGN KEY (id_zadania) REFERENCES zadanie(id_zadania) ON DELETE CASCADE,
    CONSTRAINT fk_zhs_status FOREIGN KEY (id_statusu) REFERENCES status(id_statusu) ON DELETE CASCADE
);
 

INSERT INTO zadanie_has_status (id_zadania, id_statusu) VALUES
(1, 1),
(1, 2),
(2, 1);
 

DELETE FROM projekt WHERE id_projektu = 1;
 

SELECT * FROM zadanie;
 

ALTER TABLE zadanie DROP FOREIGN KEY fk_zadanie_sprint;
 
DROP TABLE sprint;
 