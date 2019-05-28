import Control.Monad
import Data.List

getInts :: (Num a, Read a) => IO [a]
getInts = do
    line <- getLine
    return $ map read $ words line

cmp (s1, p1, _) (s2, p2, _)
    | s1 == s2 = compare (-p1) (-p2)
    | otherwise = compare s1 s2

main = do
    [n] <- getInts
    sp <- forM [1..n] $ (\i -> do
        l <- getLine
        let [s, p] = words l
        return (s, read p :: Int, i))
    mapM_ print $ map (\(_, _, x) -> x) $ sortBy cmp sp
