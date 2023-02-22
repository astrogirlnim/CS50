CREATE TABLE Transactions (id INTEGER,
    symbol TEXT NOT NULL,
    name TEXT NOT NULL,
    shares INT,
    price INT,
    total INT,
    time TIMESTAMP);

CREATE TABLE Holdings (user_id INTEGER,
    symbol TEXT,
    total_shares INT,
    current_price INT,
    new_total INT,
    stock_name TEXT);

--  Purchases table the purchases of a certain user
CREATE TABLE both AS SELECT * FROM Purchases
JOIN Holdings ON Purchases.username = Holdings.username AND Purchases.symbol = Holdings.symbol;


SELECT * FROM Holdings JOIN Transactions
ON Holdings.user_id = Transactions.id AND Holdings.symbol = Transactions.symbol;