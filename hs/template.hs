import Data.Maybe
import qualified Data.ByteString.Char8 as B

getInts = map f . B.words <$> B.getLine
    where f = fst . fromJust . B.readInteger

solve = 0

main = do
    print $ solve
