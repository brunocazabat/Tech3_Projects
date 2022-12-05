module Parser where

someFunc :: IO ()
someFunc = putStrLn "someFunc"

type Parser a = String -> Maybe (a, String)

purea :: a -> Parser a
purea x = \str -> Just (x, str)

parseChar :: Char -> Parser Char
parseChar c = \str -> case c == str!!0 of
    False -> Nothing
    True -> Just (c, tail str)

parseAnyChar :: String -> Parser Char
parseAnyChar x = \str -> do
    if length x == 1 then do
        parseChar (x!!0) str
    else do
        parseOr (parseChar (x!!0)) (parseAnyChar (tail x)) str

parseOr :: Parser a -> Parser a -> Parser a
parseOr p1 p2 = \str -> case p1 str of
    Nothing -> p2 str
    Just r1 -> Just r1

parseAnd :: Parser a -> Parser b -> Parser (a, b)
parseAnd p1 p2 = \str -> case p1 str of
    Just (f, str') -> case p2 (str') of
        Just (a, str'') -> Just ((f, a), str'')
        Nothing -> Nothing
    Nothing -> Nothing

-- parseAnd1 :: Parser (a -> b) -> Parser a -> Parser b
-- parseAnd1 p1 p2 = \str -> case p1 str of
--     Just (f, str') -> case p2 (str') of
--         Just (a, str'') -> Just ((f a), str'')
--         Nothing -> Nothing
--     Nothing -> Nothing

-- parseAndWith :: (a -> b -> c) -> Parser a -> Parser b -> Parser c
-- parseAndWith fct p1 p2 = \str -> case parseAnd1 p1 p2 str of
--     Nothing -> Nothing
--     Just ((k, l), m) -> Just ((fct k l), m)

-- (<|>) :: Parser a -> Parser a -> Parser a
-- p1 <|> p2 = \s -> let r1 = p1 s in
--     case r1 of
--         Just _ -> r1
--         Nothing -> p2 s

-- parseMany :: Parser a -> Parser [a]
-- parseMany p = ((:) <$> p <*> parseMany p) <|> pure []

-- many :: Parser a -> Parser [a]
-- many p = parseAndWith (\ x y -> [x ,y]) p (many p)
-- many p = parseOr (parseAnd1 p (many p)) purea []
-- many p = parseOr (parseAndWith (\ x y -> [x ,y]) p (many p)) purea []


-- many2 :: Parser a -> Parser [a]
-- many2 v = many_v
--     where
--         many_v = parseOr some_v purea []
--         some_v = parseAndWith (\ x y -> [x ,y]) v many_v

-- -- -- | Zero or more.
-- many :: f a -> f [a]
-- many v = many_v
--   where
--     many_v = some_v <|> pure []
--     some_v = (:) <$> v <*> many_v



    -- oneOf p1 [(:) <$> str <*> parseMany p1 str, return []]

-- parseAndWith (\ x y -> [x ,y]) p1 p1 str
-- parseAndWith (\ x y -> [x, y]) ( parseChar 'a') ( parseChar 'b') "abcd"
-- parseAnyChar x str | (k == Nothing) && (length x /= 1) = parseAnyChar (tail x) str
--                    | (k == Nothing) && (length x == 1) = Nothing
--                    | otherwise = k
--     where k = parseChar x!!0 str


    --             | x == str = "Nothing" -> Nothing
    --             | x != str = "Just" -> (c, x)
    -- where x = dropWhile (==c) s
    
    
-- parseAnyChar :: String -> Parser Char
-- parseAnyChar x str = do
--     if length x == 1 then do
--         parseChar (x!!0) str
--     else do
--         case parseChar (x!!0) str of
--             Nothing -> parseAnyChar (tail x) str
--             Just x -> Just xtr