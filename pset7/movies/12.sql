SELECT movies.title FROM
movies JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name = "Johnny Depp"
INTERSECT
SELECT movies.title FROM
movies JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name = "Helena Bonham Carter"