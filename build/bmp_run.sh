#!/bin/bash

EXEC="bmp"

# Define ANSI color codes
RESET="\e[0m"
RED="\e[31m"
GREEN="\e[32m"
ORANGE="\e[33m"
BLUE="\e[34m"
CYAN="\e[36m"

function init {
	valgrind_err=0
	pad=$(printf '%.1s' "."{1..70})
	padlength=71

	make
	if [ $? -ne 0 ]; then
		echo -e "${RED}Makefile failed!${RESET}"
		exit 1
	fi

	mkdir -p output
	mkdir -p output/basic_commands
	mkdir -p output/insert_image
	mkdir -p output/draw_commands
	mkdir -p output/fill_color
	mkdir -p output/mix_commands
}

function print_result {
	test_name="$1"
	result="$2"

	if [ "$result" == "passed" ]; then
		color="$GREEN"
	elif [ "$result" == "failed" ]; then
		color="$RED"
	else
		color="$RESET"
	fi

	printf "${ORANGE}%s${BLUE}" "Test $test_name"
	printf "%*.*s" 0 $((padlength - 9 - ${#test_name} - ${#result} )) "$pad"
	printf "${color}%s${RESET}\n" "$result"
}

function check_task {
	start_test_id=0
	end_test_id=0

	printf "${CYAN}%s............................Basic Commands.........................\n"

	for test_id in $(seq $start_test_id $end_test_id); do
		test_file="./input/basic_commands/input${test_id}.txt"
		ref_file="./ref/basic_commands/output${test_id}.bmp"
		output_file="./output/basic_commands/output${test_id}.bmp"
	
		./$EXEC < "$test_file"

		diff "$output_file" "$ref_file" &> /dev/null
		ret=$?

		if [ $ret == 0 ]; then
			print_result "$test_id" "passed"
		else 
			print_result "$test_id" "failed"
		fi

		if [ $ret == 0 ]; then
			valgrind --tool=memcheck --leak-check=full --error-exitcode=1 "./$EXEC < $input_file" &>/dev/null

			if [ $? == 1 ]; then
				print_result "valgrind" "failed"
				valgrind_err=1
			else 
				print_result "valgrind" "passed"
			fi
		else 
			print_result "valgrind" "failed"
			valgrind_err=1
		fi

		rm -f "$output_file"
	done

    echo " "

	start_test_id=0
	end_test_id=4

	printf "${CYAN}%s............................Insert Image...........................\n"

	for test_id in $(seq $start_test_id $end_test_id); do
		test_file="./input/insert_image/input${test_id}.txt"
		ref_file="./ref/insert_image/output${test_id}.bmp"
		output_file="./output/insert_image/output${test_id}.bmp"
	
		./$EXEC < "$test_file"

		diff "$output_file" "$ref_file" &> /dev/null
		ret=$?

		if [ $ret == 0 ]; then
			print_result "$test_id" "passed"
		else 
			print_result "$test_id" "failed"
		fi

		if [ $ret == 0 ]; then
			valgrind --tool=memcheck --leak-check=full --error-exitcode=1 "./$EXEC < $input_file" &>/dev/null

			if [ $? == 1 ]; then
				print_result "valgrind" "failed"
				valgrind_err=1
			else 
				print_result "valgrind" "passed"
			fi
		else 
			print_result "valgrind" "failed"
			valgrind_err=1
		fi

		rm -f "$output_file"
	done

    echo " "

	start_test_id=0
	end_test_id=3

	printf "${CYAN}%s............................Draw Commands..........................\n"

	for test_id in $(seq $start_test_id $end_test_id); do
		test_file="./input/draw_commands/input${test_id}.txt"
		ref_file="./ref/draw_commands/output${test_id}.bmp"
		output_file="./output/draw_commands/output${test_id}.bmp"
	
		./$EXEC < "$test_file"

		diff "$output_file" "$ref_file" &> /dev/null
		ret=$?

		if [ $ret == 0 ]; then
			print_result "$test_id" "passed"
		else 
			print_result "$test_id" "failed"
		fi

		if [ $ret == 0 ]; then
			valgrind --tool=memcheck --leak-check=full --error-exitcode=1 "./$EXEC < $input_file" &>/dev/null

			if [ $? == 1 ]; then
				print_result "valgrind" "failed"
				valgrind_err=1
			else 
				print_result "valgrind" "passed"
			fi
		else 
			print_result "valgrind" "failed"
			valgrind_err=1
		fi

		rm -f "$output_file"
	done

    echo " "

	start_test_id=0
	end_test_id=2

	printf "${CYAN}%s............................Fill Color.............................\n"

	for test_id in $(seq $start_test_id $end_test_id); do
		test_file="./input/fill_color/input${test_id}.txt"
		ref_file="./ref/fill_color/output${test_id}.bmp"
		output_file="./output/fill_color/output${test_id}.bmp"
	
		./$EXEC < "$test_file"

		diff "$output_file" "$ref_file" &> /dev/null
		ret=$?

		if [ $ret == 0 ]; then
			print_result "$test_id" "passed"
		else 
			print_result "$test_id" "failed"
		fi

		if [ $ret == 0 ]; then
			valgrind --tool=memcheck --leak-check=full --error-exitcode=1 "./$EXEC < $input_file" &>/dev/null

			if [ $? == 1 ]; then
				print_result "valgrind" "failed"
				valgrind_err=1
			else 
				print_result "valgrind" "passed"
			fi
		else 
			print_result "valgrind" "failed"
			valgrind_err=1
		fi

		rm -f "$output_file"
	done

    echo " "

	start_test_id=0
	end_test_id=4

	printf "${CYAN}%s............................Mix Commands...........................\n"

	for test_id in $(seq $start_test_id $end_test_id); do
		test_file="./input/mix_commands/input${test_id}.txt"
		ref_file="./ref/mix_commands/output${test_id}.bmp"
		output_file="./output/mix_commands/output${test_id}.bmp"
	
		./$EXEC < "$test_file"

		diff "$output_file" "$ref_file" &> /dev/null
		ret=$?

		if [ $ret == 0 ]; then
			print_result "$test_id" "passed"
		else 
			print_result "$test_id" "failed"
		fi

		if [ $ret == 0 ]; then
			valgrind --tool=memcheck --leak-check=full --error-exitcode=1 "./$EXEC < $input_file" &>/dev/null

			if [ $? == 1 ]; then
				print_result "valgrind" "failed"
				valgrind_err=1
			else 
				print_result "valgrind" "passed"
			fi
		else 
			print_result "valgrind" "failed"
			valgrind_err=1
		fi

		rm -f "$output_file"
	done

    echo -e " "
}

init
check_task
make clean &> /dev/null
