cd ../build

killall test_server 2> /dev/null
./test_server -l d -e -x 1 > /dev/null &
sleep 1

clear_log() {
    >clog
    >slog
}

grep_err_log() {
    grep "\[error\]" clog
    grep "\[error\]" slog
    #grep "retrans rate:" clog|grep -v "retrans rate:0.0000"
    #grep "retrans rate:" slog|grep -v "retrans rate:0.0000"
}

function case_print_result() {
    echo "[ RUN      ] xquic_case_test.$1"
    if [ "$2" = "pass" ];then
        echo "[       OK ] xquic_case_test.$1 (1 ms)"
    else
        echo "[     FAIL ] xquic_case_test.$1 (1 ms)"
    fi
}

clear_log
echo -e "1% loss ...\c"
result=`./test_client -s 10240000 -l d -E -d 10|grep ">>>>>>>> pass"`
errlog=`grep_err_log`
echo "$result"
if [ -z "$errlog" ] && [ "$result" == ">>>>>>>> pass:1" ]; then
    case_print_result "1_percent_loss" "pass"
else
    case_print_result "1_percent_loss" "fail"
    echo "$errlog"
fi

clear_log
echo -e "3% loss ...\c"
result=`./test_client -s 10240000 -l d -E -d 30|grep ">>>>>>>> pass"`
errlog=`grep_err_log`
echo "$result"
if [ -z "$errlog" ] && [ "$result" == ">>>>>>>> pass:1" ]; then
    case_print_result "3_percent_loss" "pass"
else
    case_print_result "3_percent_loss" "fail"
    echo "$errlog"
fi

clear_log
result=`./test_client -s 10240000 -t 5 -l d -E -d 100|grep ">>>>>>>> pass"`
errlog=`grep_err_log`
if [ -z "$errlog" ] && [ "$result" == ">>>>>>>> pass:1" ]; then
    case_print_result "10_percent_loss" "pass"
else
    case_print_result "10_percent_loss" "fail"
    echo "$errlog"
fi
echo -e "10% loss ...\c"
echo "$result"

killall test_server 2> /dev/null