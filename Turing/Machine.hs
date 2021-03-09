module Turing.Machine (newTM, runTM) where


import Turing.Base
import Turing.MConfig


-- The actual machine!
data Machine = Machine Tape MConfig 

instance Show Machine where 
    show (Machine tape (MConfig name _)) = showTapeWith ("", '/' : name ++ "") tape

newTM mconfig = Machine blankTape mconfig

findNextMConfig :: Symbol -> MConfig -> ([Operation], MConfig)
findNextMConfig s (MConfig name cbs) = fmb s cbs
    where fmb s [] = error $ "Incomplete machine configuration: can't find match for symbol \"" ++ s ++ "\" in " ++ name ++ "!"
          fmb s (cb@((sspec, Behaviour ops fmc)):cbs) | sspec `matches` s = (ops, fmc) 
                                                      | otherwise = fmb s cbs

move :: Machine -> Machine
move (Machine tape mconfig) = Machine nextTape nextMConfig
    where sym = readSymbol tape
          (ops, nextMConfig) = findNextMConfig sym mconfig
          nextTape = foldl (\acc o -> apply o acc) tape ops

moves :: Machine -> [Machine]
moves tm = tm : moves (move tm)

stepTM :: Int -> Machine -> IO ()
stepTM n tm = sequence_ . take n . map (\(m, n) -> print m) $ zip (moves tm) [0..]

runTM :: Int -> Machine -> IO ()
runTM n = print . last . take n . moves
