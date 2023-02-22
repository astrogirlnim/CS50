-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check database structure
.schema

-- Look at the Crime Scene Reports from July 28th, 2020 on Chamberlin Street.
-- Log says crime took place at 10:15 am at courthouse. 3 witnesses.
SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street LIKE 'Chamberlin Street';

-- Look for interview transcripts which mention the courthouse.
-- Ruth says within 10 minutes of the thefth thief drove away from courthouse. Check cars which left then.
-- Eugene says thief withdrew from ATM on Fifer Street that morning.
-- Raymond says the thief was taking earliest flight out from Fiftyville next morning.
-- Raymond says thief told person on the phone to purchase flight ticket.
SELECT * FROM interviews WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE '%courthouse%';

-- Look at courthouse security logs and create list of suspects
CREATE TABLE suspects AS
SELECT DISTINCT(people.name) FROM courthouse_security_logs
JOIN people ON people.license_plate = courthouse_security_logs.license_plate
WHERE courthouse_security_logs.year = 2020
AND courthouse_security_logs.month = 7
AND courthouse_security_logs.day = 28
AND courthouse_security_logs.minute <= 25
AND courthouse_security_logs.minute >= 15
AND courthouse_security_logs.activity LIKE 'exit'
ORDER BY people.name ASC;

-- Check ATM withdrawals that morning which match suspect names
ALTER TABLE suspects
ADD atm_suspects TEXT;


INSERT INTO suspects(atm_suspects)
SELECT DISTINCT(name) FROM people
JOIN bank_accounts ON people.id = person_id
WHERE name IN (SELECT name FROM suspects)
AND bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28
AND transaction_type = 'withdraw');

-- Check which suspects are on next day earliest flight.
ALTER TABLE suspects
ADD flight_suspects TEXT;

INSERT INTO suspects(flight_suspects)
SELECT DISTINCT(name) FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE flight_id IN
(SELECT id FROM flights
WHERE year = 2020 AND month = 7 AND day = 29
ORDER BY hour,minute ASC LIMIT 1)
AND name IN (SELECT atm_suspects FROM suspects);

-- Check which suspects called within a minute of the event for less than a minute.
-- Ernest did it.
ALTER TABLE suspects
ADD call_suspects TEXT;

INSERT INTO suspects(call_suspects)
SELECT DISTINCT(name) FROM people
WHERE name IN (SELECT flight_suspects FROM suspects)
AND phone_number IN
(SELECT caller FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);

--See where Ernest went and who he called
-- Escape: London.
SELECT city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
WHERE flights.id IN
(SELECT flight_id FROM passengers
JOIN people ON people.passport_number = passengers.passport_number
WHERE name IN (SELECT call_suspects FROM suspects))
AND year = 2020 AND month = 7 AND day = 29;


-- Accomplice: Berthold.
SELECT name FROM people
WHERE phone_number IN
(SELECT receiver FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE name IN (SELECT call_suspects FROM suspects)
AND year = 2020 AND month = 7 AND day = 28 AND duration < 60);