import Data.Maybe
import qualified Data.ByteString.Char8 as B

readInts = map f . B.words <$> B.getLine
    where f = fst . fromJust . B.readInteger

f a b
    | m == 0 = 2 * a - b
    | otherwise = 2 * a + f a' b'
    where
    m = a `mod` b
    a' = max m (b - m)
    b' = min m (b - m)

main = do
    [n, x] <- readInts
    let a = max x (n - x)
        b = min x (n - x)
    print $ n + f a b
