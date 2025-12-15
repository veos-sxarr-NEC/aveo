#!/bin/bash
#
# Super simple run loop for running the tests for AVEO.
# Can be improved a lot...
#
SCRIPTPATH=$(dirname $(realpath ${BASH_SOURCE[0]}))
LIBEXECDIR=$(realpath $SCRIPTPATH/../libexec)
good=0
bad=0

declare -A failed

for t in test_*; do
    echo
    echo "## running $t ##"
    echo
    #
    # run static test
    #
    if [ "${t%_static}" != "$t" ]; then
	./$t
        if [ $? -ne 0 ]; then
            bad=$((bad+1))
            failed[$t]=1
        else
            good=$((good+1))
        fi
	continue
    fi
    #
    # run ftrace test
    #
    if [ "${t%_ftrace}" != "$t" ]; then
	[ -f ftrace.out ] && rm -f ftrace.out
        TMPFILE=$(mktemp ./aveo_testXXXXXXX)
        trap "rm -f ${TMPFILE}" EXIT
        if [ -x VEORUN_BIN=$LIBEXECDIR/aveorun-ftrace ]; then
            env VEORUN_BIN=$LIBEXECDIR/aveorun-ftrace ./$t > ${TMPFILE}
        else
            ./$t > ${TMPFILE}
        fi
        if [ $? -ne 0 ]; then
            bad=$((bad+1))
            failed[$t]=1
        else
            good=$((good+1))
        fi
	sleep 1
        (
	    [ -n $VE_NODE_NUMBER ] && VE_NODE_NUMBER=0
	    FTRACE_PID=$( cat ${TMPFILE} | awk '{ print $3 }' )
	    echo $FTRACE_PID
	    FTRACE_FILENAME="ftrace.out.veo.$VE_NODE_NUMBER.$FTRACE_PID"
	    [ -f $FTRACE_FILENAME ] || ( echo "no ftrace.out"; exit 1; )
	    /opt/nec/ve/bin/ftrace -f $FTRACE_FILENAME || exit 1
        )
        if [ $? -ne 0 ]; then
            bad=$((bad+1))
            failed[$t]=1
        else
            good=$((good+1))
        fi
	sleep 1
	continue
    fi
    #
    # run normal dynamic test
    #
    if [ -x VEORUN_BIN=$LIBEXECDIR/aveorun ]; then
        env VEORUN_BIN=$LIBEXECDIR/aveorun ./$t
    else
        ./$t
    fi

    if [ $? -ne 0 ]; then
        bad=$((bad+1))
        failed[$t]=1
    else
        good=$((good+1))
    fi
    echo
done

echo
echo "============================================================"
echo "$good tests passed"
echo "$bad tests failed"

if [ $bad -gt 0 ]; then
    echo
    echo "The failed tests were:"
    echo ${!failed[*]}
fi

echo "============================================================"

