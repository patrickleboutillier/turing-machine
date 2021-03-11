module Turing.Machine (newTM, newTMM, stepTM, runTM, Machine(..)) where


import Turing.Base
import Turing.MConfig
import Turing.StdForm

-- The actual machine!
data Machine = Machine Domain Tape MConfig 

instance Show Machine where 
    show (Machine dom tape (MConfig name _)) = showTapeWith ("", '/' : name ++ "") tape

newTM :: Domain -> MConfig -> Machine
newTM dom mc = Machine dom blankTape mc

newTMM :: Domain -> MConfig -> Machine -> Machine
newTMM dom mc (Machine dom' tape mc') = Machine dom (toStandardTape tbl) mc
    where tbl = asTable dom' mc'

findNextMConfig :: Symbol -> MConfig -> ([Operation], MConfig)
findNextMConfig s (MConfig name cbs) = fmb s cbs
    where fmb s [] = error $ "Incomplete machine configuration: can't find match for symbol \"" ++ s ++ "\" in " ++ name ++ "!"
          fmb s (cb@((sspec, Behaviour ops fmc)):cbs) | sspec `matches` s = (ops, fmc) 
                                                      | otherwise = fmb s cbs

move :: Machine -> Machine
move (Machine dom tape mc) = Machine dom nextTape nextmc
    where sym = scanSymbol tape
          (ops, nextmc) = findNextMConfig sym mc
          nextTape = foldl (\acc o -> apply o acc) tape ops

moves :: Machine -> [Machine]
moves tm = tm : moves (move tm)

stepTM :: Int -> Machine -> IO ()
stepTM n tm = sequence_ . take n . map (\(m, n) -> print m) $ zip (moves tm) [0..]

runTM :: Int -> Machine -> IO ()
runTM n = print . last . take n . moves
