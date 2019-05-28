import qualified Data.Heap as Heap
import Data.List
import Control.Monad

getVals :: Read a => IO [a]
getVals = getLine >>= (return . map read . words)
getStrs = getLine >>= (return . words)

f (heap, ans) Left (s, t, x) = (insert (x, t), ans)
f (heap, ans) Right d
    | null heap = (heap, (-1):ans)
    | t-x <= d = f (deleteMin heap, ans) Right d
    | otherwise = (heap, x:ans)
    where (x, t) = minimum heap

solve stxs ds = reverse $ snd $ foldl f (empty, []) way
    where
        wayTo = [Left (s, t, x) | [s, t, x] <- stxs]
        wayFrom = [(Right d) | d <- ds]
        way = sortBy cmp $ wayTo ++ wayFrom
        cmp Left (s1, t1, x1) Left (s2, t2, x2) = compare (s1-x1) (s2-x2)
        cmp Left (s, t, x) Right d
            | s-x == d = LT
            | otherwise = compare (s-x) d
        cmp Right d1 Right d2 = compare d1 d2



main = do
    [n, q] <- getVals
    stxs <- replicateM n getVals
    ds <- replicateM q getVals
    print $ solve stxs ds