main = do
    n <- readLn
    t <- sequence (take n $ repeat readLn)
    print $ solve t

solve :: [Integer] -> Integer
solve t = minimum t
