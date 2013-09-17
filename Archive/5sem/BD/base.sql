DROP TABLE staff, rooms, rooms_staff, collections, exhibits;

-- Сотрудники музея

CREATE TABLE staff
(
	id serial PRIMARY KEY,
	last_name text NOT NULL, -- Фамилия
	first_name text NOT NULL, -- Имя
	second_name text -- Отчество
);

-- Залы музея

CREATE TABLE rooms
(
	id serial PRIMARY KEY,
	name text UNIQUE NOT NULL, -- Название
	size integer NOT NULL -- Размер в м2
);

-- Кто где и кем работает

CREATE TABLE rooms_staff
(
	room_id integer CONSTRAINT rooms_fk REFERENCES rooms(id), -- Зал
	employee_id integer CONSTRAINT staff_fk REFERENCES staff(id), -- Сотрудник 
	post text NOT NULL, -- Должность
	UNIQUE(room_id, employee_id)
);

-- Собрания экспонатов

CREATE TABLE collections
(
	id serial PRIMARY KEY,
	name text NOT NULL, -- Название
	room_id integer NOT NULL CONSTRAINT rooms_fk REFERENCES rooms(id) -- Зал
);

-- Экспонаты

CREATE TABLE exhibits
(
	id serial PRIMARY KEY,
	name text NOT NULL, -- Название
	collection_id integer NOT NULL CONSTRAINT collections_fk REFERENCES collections(id), -- К какой коллекции относится
	value float NOT NULL -- Ценность в руб
);

INSERT INTO staff(last_name, first_name, second_name) VALUES('Себастьянова', 'Елена', 'Петровна');
INSERT INTO staff(last_name, first_name, second_name) VALUES('Купцова', 'Екатерина', 'Ивановна');
INSERT INTO staff(last_name, first_name, second_name) VALUES('Антоненко', 'Вадим', 'Самойлович');
INSERT INTO staff(last_name, first_name, second_name) VALUES('Ребров', 'Иван', 'Алексеевич');
INSERT INTO staff(last_name, first_name, second_name) VALUES('Пупкин', 'Станислав', 'Иванович');
	
INSERT INTO rooms(name, size) VALUES('Зал народов востока', 200);
INSERT INTO rooms(name, size) VALUES('Зал европейской культуры', 400);

INSERT INTO rooms_staff(room_id, employee_id, post) VALUES(1, 1, 'Смотритель');
INSERT INTO rooms_staff(room_id, employee_id, post) VALUES(1, 2, 'Экскурсовод');
INSERT INTO rooms_staff(room_id, employee_id, post) VALUES(2, 3, 'Смотритель');
INSERT INTO rooms_staff(room_id, employee_id, post) VALUES(2, 4, 'Экскурсовод');

INSERT INTO collections(name, room_id) VALUES('Оружие средневековой Европы', 2);
INSERT INTO collections(name, room_id) VALUES('Одежда народов востока', 1);

INSERT INTO exhibits(name, collection_id, value) VALUES('Индийский саронг. 2 век н.э.', 2, '2000.00');
INSERT INTO exhibits(name, collection_id, value) VALUES('Палаш, инкрустированный алмазами', 1, '200000.00');
INSERT INTO exhibits(name, collection_id, value) VALUES('Арабская паранжа. 4 век н.э.', 2, '3000.00');
INSERT INTO exhibits(name, collection_id, value) VALUES('Рыцарский цеп. 14 век.', 1, '12000.00');
INSERT INTO exhibits(name, collection_id, value) VALUES('Алебарда. 13 век', 1, '42000.00');
INSERT INTO exhibits(name, collection_id, value) VALUES('Японское кимоно. 12 век', 2, '27000.00');
