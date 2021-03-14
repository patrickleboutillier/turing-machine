module Turing.Machine (moves, newTM, newTMM, stepTM, runTM, Machine(..)) where

import Turing.Base
import Turing.MConfig
import Turing.StdForm


-- The actual machine!
data Machine = Machine Tape MConfig 

instance Show Machine where 
    show (Machine tape (MConfig name _)) = showTapeWith ("", '/' : name ++ "") tape

newTM :: MConfig -> Machine
newTM mc = Machine blankTape mc

newTMM :: MConfig -> Machine -> Machine
newTMM mc (Machine tape mc') = Machine (toStandardTape tbl) mc
    where tbl = asTable mc'

findNextMConfig :: Symbol -> MConfig -> ([Operation], MConfig)
findNextMConfig s (DynMConfig f) = findNextMConfig s $ f s
findNextMConfig s (MConfig name cbs) = fmb s cbs
    where fmb s [] = error $ "Incomplete machine configuration: can't find match for symbol \"" ++ s ++ "\" in " ++ name ++ "!"
          fmb s (cb@((sspec, Behaviour ops fmc)):cbs) | sspec `matches` s = (ops, fmc) 
                                                      | otherwise = fmb s cbs
                                                      
move :: Machine -> Machine
move (Machine tape mc) = Machine nextTape nextmc
    where sym = scanSymbol tape
          (ops, nextmc) = findNextMConfig sym mc
          nextTape = foldl (\acc o -> apply o acc) tape ops

moves :: Machine -> [Machine]
moves tm = tm : moves (move tm)

stepTM :: Int -> Machine -> IO ()
stepTM n tm = sequence_ . take n . map print $ moves tm

runTM :: Int -> Machine -> IO ()
runTM n = print . last . take n . moves
