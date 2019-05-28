import Data.List
import Control.Monad

getVals :: Read a => IO [a]
getVals = getLine >>= (return . map read . words)
getStrs = getLine >>= (return . words)

solve = 0

main = do
    print $ solve