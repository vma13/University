-- 1) Написать  запрос вычисляющий какой из залов содержит самый дорогой набор экспонатов--
SELECT rs.name FROM (
  SELECT r.name, sum(e.value) FROM
    rooms r JOIN
    collections c ON r.id = c.room_id JOIN
    exhibits e ON c.id = e.collection_id
    GROUP BY c.id, r.name
    ORDER BY sum DESC
    LIMIT 1
  ) rs
;
-- 2) Написать запрос, находящий в каком зале на сотрудников приходиться в среднем больше всего экспонатов. --
SELECT ra.name FROM
  (SELECT rec.name, cast(rec.count as float) / cast(rsc.count as float) as ans FROM
    (SELECT room_id, count(*) FROM rooms_staff GROUP BY room_id) rsc JOIN
    (SELECT r.id, r.name, count(*) FROM
      rooms r JOIN
      collections c ON c.room_id = r.id JOIN
      exhibits e ON e.collection_id = c.id
      GROUP BY r.id, r.name) rec ON rsc.room_id = rec.id
    ORDER BY ans DESC
    LIMIT 1
  ) ra
;
-- 3) Написать запрос удаляющий 10 самых дешевых экспонатов. --
DELETE FROM exhibits WHERE id IN (
SELECT id FROM exhibits ORDER BY value LIMIT 10
);
-- 4) Написать запрос, который во всех залах, где наибольшее число экскурсоводов, одного из них делает смотрителем.--
UPDATE rooms_staff
  SET post = 'Смотритель'
  WHERE (room_id, employee_id) IN (
    SELECT room_id, max(employee_id) FROM rooms_staff
      WHERE (room_id, employee_id) IN (
        SELECT room_id, employee_id
          FROM rooms_staff
          WHERE room_id IN (
            SELECT room_id
              FROM (
                SELECT room_id, count(*)
                  FROM rooms_staff
                  WHERE post = 'Экскурсовод'
                  GROUP BY room_id
              ) as rc
              WHERE rc.count = (
                SELECT count(*)
                  FROM rooms_staff
                  WHERE post = 'Экскурсовод'
                  GROUP BY room_id
                  ORDER BY count DESC
                  LIMIT 1
              )
            )
            AND post = 'Экскурсовод'
      )
      GROUP BY room_id
  )
;
