--1
SELECT name FROM room WHERE id=(
SELECT room_id FROM collections WHERE id=(
SELECT colection_id FROM
-- не сделано



--1 написать запрос, вычисляющий какой из залов содержит самый дорогой набор экспанатов
(1)
SELECT rooms.id, sum(exhibits.value)
       FROM rooms INNER JOIN collections on
       id = romm_id INNER JOIN exhibits on
       collections_id = collectins.id
       GROUP BY rooms.id 

(2)
SELECT max(sum FROM t)

SELECT * FROM (1) WHERE (SELECT max(sum) FROM ((SELECT rooms.id, sum(exhibits.value)
       		     FROM rooms INNER JOIN collections on
       		     id = romm_id INNER JOIN exhibits on
       		     collections_id = collectins.id
       		     GROUP BY rooms.id) t) )
		     sum = (2)

--


--2 
(1)
(SELECT staff.id, count(*)  
       FROM staff s INNER JOIN rooms_staff rs ON
       s.id = rs.emploed_id INNER JOIN collection c
       using(rooms_id) INNER JOIN exhibits e ON
       c.id = e.collection_id  
       GROUP BY staff.id) t 
       
SELECT avg(count) FROM (1);


--3

DELETE FROM exhibits WHERE id IN (SELECT id FROM exhibits ORDER BY value LIMIT 10);

--4 
update collections set room_id = 1 where collections.id = (
SELECT c.id, sum(value)
       FROM collections c inner join  exhibits e 
       on c.id = e.colections_id group by c.id
       order by sum(value) limit 1);

--5
(1)
SELECT max(count) from 
       ((SELECT id_room, count(*)
       	       FROM rooms_staff where post = "экскурсовод" 
	       group by room_id) t
(2)   
SELECT room_id from 
       	       rooms_staff where post = "Экскурсовод" group by 
	       room_id having count(*) = (1)
	       
 update rooms_staff set post = "смотритель" where
 	employee in( SELECT distinct on room_id employee_id 
	from rooms_staff where room_id in ((2)) and post = "Экскурсовод" )

--добавляющий во все залы где экспонатов больше 1000 нового смотрителя 
