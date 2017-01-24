main = do
    line <- getLine
    let x:y:_ = map read $ words line
    putStrLn $ show $ solve x y

solve x y = div y x
