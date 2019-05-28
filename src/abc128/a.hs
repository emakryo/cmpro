main = do
    line <- getLine
    let [a, p] = map read $ words line :: [Integer]
    print $ solve a p

solve a p = div (3*a+p) 2
