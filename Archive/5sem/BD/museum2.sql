--2 - 1
SELECT (cast (sum(se.count) as float))/count(*) FROM (
  SELECT count(*) FROM
    rooms_staff rs JOIN
    rooms r ON (rs.room_id = r.id) JOIN
    staff s ON (rs.employee_id = s.id) JOIN
    collections c ON (c.room_id = r.id) JOIN
    exhibits e ON (e.collection_id = c.id)
  GROUP BY s.id) as se
;

--2 - 2
SELECT se.last_name, se.first_name, se.second_name FROM
  (SELECT s.last_name, s.first_name, s.second_name, max(e.value) FROM
    rooms_staff rs JOIN
    rooms r ON (rs.room_id = r.id) JOIN
    staff s ON (rs.employee_id = s.id AND rs.post = 'Экскурсовод') JOIN
    collections c ON (c.room_id = r.id) JOIN
    exhibits e ON (e.collection_id = c.id)
  GROUP BY s.id, s.last_name, s.first_name, s.second_name
  ORDER BY max DESC LIMIT 1) as se
;

--2 - 3
UPDATE collections SET room_id = 1 WHERE id IN (
  SELECT ce.collection_id FROM
    (SELECT e.collection_id, sum(e.value) FROM
      collections c JOIN
      exhibits e ON (e.collection_id = c.id)
    GROUP BY c.id, e.collection_id
    ORDER BY sum ASC LIMIT 1) as ce
  )
;

--2 - 4
INSERT INTO rooms_staff(room_id, employee_id, post)
  SELECT re.id, staff.id, 'Смотритель' FROM (
    SELECT r.id, count(*) FROM
      rooms r JOIN
      collections c ON (c.room_id = r.id) JOIN
      exhibits e ON (e.collection_id = c.id)
    GROUP BY r.id
  ) as re,
  staff WHERE
    re.count > 1000 AND
    staff.last_name = 'Пупкин' AND
    staff.first_name = 'Станислав' AND
    staff.second_name = 'Иванович'
;
