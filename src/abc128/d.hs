import Data.List
import Control.Monad

getVals :: Read a => IO [a]
getVals = getLine >>= (return . map read . words)
getStrs = getLine >>= (return . words)

solve' n k vs = [(calc a b k vs, (a, b)) | a <- [0..m], b <- [0..m-a]]
    where
        m = min n k
solve n k vs = fst $ maximum $ solve' n k vs 
calc a b k vs = sum largest
    where
        largest = take (max n_positive $ 2*a+2*b-k) $ reverse $ sort full
        n_positive = length $ filter (\x -> x >= 0) full
        full = (take a vs) ++ (take b $ reverse vs)

main = do
    [n, k] <- getVals :: IO [Int]
    vs <- getVals :: IO [Integer]
    print $ solve n k vs