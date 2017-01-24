main = do
    t <- readLn
    _ <- getLine
    a <- (map read . words) <$> getLine
    _ <- getLine
    b <- (map read . words) <$> getLine
    putStrLn $ output $ solve t a b

solve :: Int -> [Int] -> [Int] -> Bool
solve t a [] = True
solve t [] b = False
solve t (a:as) (b:bs)
    | a <= b && b <= a+t = solve t as bs
    | a+t < b = solve t as (b:bs)
    | otherwise = False

output :: Bool -> String
output True = "yes"
output False = "no"
