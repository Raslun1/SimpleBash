#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="test_case_cat.txt"
echo "" > log.txt

for var in -b -e -n -s -t -v 
do
          TEST1="$var $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo " SUCCESS"
            else
              echo $DIFF_RES
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
              echo " FAIL"
          fi
          rm s21_cat.txt cat.txt
done

for var in -b -e -n -s -t -v 
do
  for var2 in -b -e -n -s -t -v 
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo " SUCCESS"
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
              echo " FAIL"
          fi
          rm s21_cat.txt cat.txt
        fi
  done
done

for var in -b -e -n -s -t -v 
do
  for var2 in -b -e -n -s -t -v 
  do
      for var3 in -b -e -n -s -t -v 
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="$var $var2 $var3 $TEST_FILE"
          echo "$TEST1"
          ./s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
              echo " SUCCESS"
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
              echo " FAIL"
          fi
          rm s21_cat.txt cat.txt

        fi
      done
  done
done

for var in -b -e -n -s -t -v 
do
  for var2 in -b -e -n -s -t -v 
  do
      for var3 in -b -e -n -s -t -v 
      do
          for var4 in -b -e -n -s -t -v 
          do
            if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
            then
              TEST1="$var $var2 $var3 $var4 $TEST_FILE"
              echo "$TEST1"
              ./s21_cat $TEST1 > s21_cat.txt
              cat $TEST1 > cat.txt
              DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
              if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
                then
                  (( COUNTER_SUCCESS++ ))
                  echo " SUCCESS"
                else
                  echo "$TEST1" >> log.txt
                  (( COUNTER_FAIL++ ))
                  echo " FAIL"
              fi
              rm s21_cat.txt cat.txt

            fi
          done
      done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
