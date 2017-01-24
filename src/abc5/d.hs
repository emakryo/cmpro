import Control.Monad

main = do
    n <- readLn
    d <- replicateM n $ map read . words <$> getLine
    q <- readLn
    p <- replicateM q $ readLn
    mapM_ print $ solve d p

solve :: [[Int]] -> [Int] -> [Int]
solve d p = map (solve_ $ cum d) p

solve_ d p = maximum [solve__ d (x-1,y-1) (x+dx-1,y+dy-1) |
                      x <- [0..n], y <- [0..n],
                      q <- [1..p],
                      dx <- [1..n], let dy = div q dx, 1 <= dy, dy <= n, mod q dx == 0,
                      x+dx <= n, y+dy <= n]
    where
    n = length d

solve__ d (-1, -1) (x', y') = d!!x'!!y'
solve__ d (-1, y) (x', y') = d!!x'!!y' - d!!x'!!y
solve__ d (x, -1) (x', y') = d!!x'!!y' - d!!x!!y'
solve__ d (x, y) (x', y') = d!!x'!!y'-d!!x'!!y-d!!x!!y'+d!!x!!y

cum x = scanl1 (zipWith (+)) (map (scanl1 (+)) x)
