import Data.Bits
import Data.List
import Control.Monad

getVals :: Read a => IO [a]
getVals = getLine >>= (return . map read . words)
getStrs = getLine >>= (return . words)

toBits ss = [sum [(shift 1 $ si-1) | si <- s] | s <- ss]
check i (b, p) = p == (popCount $ b .&. i) `mod` 2
solve n ss ps = length [i | i <- [0..(shift 1 n)-1] :: [Int], 
                        all (check i) xs]
    where
        xs = zip (toBits ss) ps

main = do
    [n, m] <- getVals :: IO [Int]
    ss <- replicateM m $ getVals >>= (return . tail) :: IO [[Int]]
    ps <- getVals :: IO [Int]
    print $ solve n ss ps