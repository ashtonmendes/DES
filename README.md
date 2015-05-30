'''html
<!-- saved from url=(0046)http://merlot.usc.edu/cs531-s15/homeworks/hw5/ -->
<html><head><meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<title>Homework #5 - CSCI 531, Spring 2015</title>
<link href="./Homework #5 - CSCI 531, Spring 2015_files/cs531bc.css" rel="stylesheet" type="text/css">
<link rev="made" href="mailto:bill.cheng@acm.org"><style type="text/css"></style></head>
<body bgcolor="#FFFFFF" link="#D02090" vlink="#996600" alink="#990000">

<table border="0" cellpadding="0" cellspacing="0" width="100%">
<tbody><tr><td align="CENTER" valign="TOP" width="112">
    <!-- COL 1, should be identical to all other pages here -->
    <table border="0" cellpadding="0" cellspacing="0" width="113">
    <tbody><tr><td align="CENTER" valign="TOP" width="112">
        &nbsp;
        </td>
    </tr>
    <tr><td align="CENTER" valign="TOP" width="112">
        <a href="http://www.cs.usc.edu/"><img src="./Homework #5 - CSCI 531, Spring 2015_files/usctommy.gif" alt="USC CSD Home" border="0"></a>
        <!-- BR>&nbsp;<BR -->
        <!-- IMG SRC="images/small-uc.gif" BORDER=0 -->
        </td>
    </tr>
    </tbody></table>
    </td>
    <!-- TD ALIGN=LEFT VALIGN=TOP WIDTH=13 -->
    <!-- COL 2, should be identical to all other pages here -->
        <!-- IMG SRC="images/spacer.gif" HEIGHT=1 WIDTH=13 -->
    <!-- /TD -->
    <td align="LEFT" valign="TOP">
    <!-- COL 3, every page should be different -->
        <br><table border="0">
        <!-- Page Header -->
        <tbody><tr><td align="LEFT" valigh="TOP">
                <a href="http://merlot.usc.edu/cs531-s15/">Spring 2015</a><a>
            </a></td>
            <td align="RIGHT" valigh="TOP">
                <a href="http://merlot.usc.edu/cs531-s15/">CSCI 531</a><br>
            </td>
        </tr>
        
        <!-- Page Title -->
        <tr><td colspan="3" align="CENTER">
                <h2>Homework #5</h2>
                <h4>(100 points total)</h4>
                <h2>DES</h2>
                <b><i>Due 11:45PM
                3/27/2015 (firm)</i></b>
                <!--
                <H3><FONT COLOR="red"><I>(Under Construction -
                    Anything Can Change without Notice)</I></FONT></H3>
                  -->
            </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <!-- Section -->
        <tr><td colspan="3" align="LEFT" bgcolor="#000000" width="100%">
                <font color="#ffffff"><a name="intro"><b>Assignment</b></a></font>
            </td>
        </tr>
        <!-- Top Section -->
        <tr><td colspan="3" align="LEFT">
The purpose of this assignment is to get you familiar with
DES by implementing DES from scratch with the flexibility
of changing some of the internal tables.  For this assignment,
you are <b>not</b> allowed to use publicly available DES-specific
code (generic public code for parsing input data is allowed).

<p>

Please see the
<a href="http://merlot.usc.edu/cs531-s15/lectures.html#tentative">lecture slides on DES</a> or section
7.4 on pages 250-256 of the
<a href="http://www.cacr.math.uwaterloo.ca/hac/">
textbook (Handbook of Applied Cryptography)</a> (in Chapter 7).

</p><p>

<a href="http://merlot.usc.edu/cs531-s15/homeworks/hw5/#submit">Electronic submissions</a> only.
            </p></td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <!-- Section -->
        <tr><td colspan="3" align="LEFT" bgcolor="#000000" width="100%">
                <font color="#ffffff"><a name="compile"><b>Compiling</b></a></font>
            </td>
        </tr>
        <!-- Top Section -->
        <tr><td colspan="3" align="LEFT">
Please use a <tt>Makefile</tt> so that when the grader simply enters:
    <pre>    make hw5</pre>
an executable named <b>hw5</b> is created.
(Minor variation on the <tt>make</tt> command is allowed.)
Please make sure that your submission conforms to
<a href="http://merlot.usc.edu/cs531-s15/makefile.html#requirements">other
general compilation requirements</a>.
            </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <!-- Section -->
        <tr><td colspan="3" align="LEFT" bgcolor="#000000" width="100%">
                <font color="#ffffff"><a name="syntax"><b>Commandline Syntax &amp; Program
                Output</b></a></font>
            </td>
        </tr>
        <!-- Top Section -->
        <tr><td colspan="3" align="LEFT">
The commandline syntax for <b>hw5</b> is as follows:

<pre>    <b>hw5</b> <b>tablecheck</b> <b>-t=</b>tablefile
    <b>hw5</b> <b>encrypt</b> <b>-k=</b>key <b>-t=</b>tablefile [file]
    <b>hw5</b> <b>decrypt</b> <b>-k=</b>key <b>-t=</b>tablefile [file]
    <b>hw5</b> <b>encrypt3</b> <b>-k=</b>key3 <b>-t=</b>tablefile [file]
    <b>hw5</b> <b>decrypt3</b> <b>-k=</b>key3 <b>-t=</b>tablefile [file]</pre>

<p>

Square bracketed items are optional.
You must follow the UNIX convention that <b>commandline options</b>
can come in any order.  (Note: a <b>commandline option</b> is a
commandline argument that begins with a <b>-</b> character in a
commandline syntax specification.)
If an input file is not specified, your program should
read from <tt>stdin</tt>.
Output of your program must go to <tt>stdout</tt> and
error messages must go to <tt>stderr</tt>.

</p><p>

The meaning of the commands are:

</p><blockquote>
<table border="0" cellpadding="0" cellspacing="0">
    <tbody><tr><td align="LEFT" valign="TOP"><b>tablecheck</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">Check the integrity of <tt>tablefile</tt>.
                       Please see <a href="http://merlot.usc.edu/cs531-s15/homeworks/hw5/#format">tablefile format</a>
                       to see the requirements.
        </td>
    </tr>
    <tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>encrypt</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">Encrypts the input using DES driven by
                       <tt>tablefile</tt> in the ECB mode using <tt>key</tt>
                       as the encryption key
                       (8-byte long and in hexstring format).
                       If the filesize of the input is not a multiple of
                       8 bytes, please pad it with zeroes.
                       (Please treat <tt>file</tt> as a binary file.)
        </td>
    </tr>
    <tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>decrypt</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">Decrypts the input using DES driven by
                       <tt>tablefile</tt> in the ECB mode using <tt>key</tt>
                       as the encryption key
                       (8-byte long and in hexstring format).
                       If the filesize of the input is not a multiple of
                       8 bytes, please pad it with zeroes.
                       (Please treat <tt>file</tt> as a binary file.)
        </td>
    </tr>
    <tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>encrypt3</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">Encrypts the input using EDE triple DES driven by
                       <tt>tablefile</tt> in the ECB mode using <tt>key3</tt>
                       as the encryption key
                       (24-byte long and in hexstring format).
                       If the filesize of the input is not a multiple of
                       8 bytes, please pad it with zeroes.
                       (Please treat <tt>file</tt> as a binary file.)
        </td>
    </tr>
    <tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>decrypt3</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP"><span class="update">[BC: updated 3/24/2015]</span>
                       Decrypts the input (assuming it was created using the "<tt>encrypt3</tt>" command) driven by
                       <tt>tablefile</tt> in the ECB mode using <tt>key3</tt>
                       as the encryption key
                       (24-byte long and in hexstring format).
                       If the filesize of the input is not a multiple of
                       8 bytes, please pad it with zeroes.
                       (Please treat <tt>file</tt> as a binary file.)
        </td>
    </tr>
</tbody></table>
</blockquote>

<p>

The output for various commands are as follows.

</p><blockquote>
<table border="0" cellpadding="0" cellspacing="0">
    <tbody><tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>tablecheck</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">
            The command should produce no output in <tt>stdout</tt>.
            All error output must go to <tt>stderr</tt>.
        </td>
    </tr>
    <tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>encrypt</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">
            The output of this command is a binary file where each
            8-byte block is a direct DES encryption of the corresponding
            input 8-byte block.
            <p>
            You must also output, to <tt>stderr</tt>, the values of the subkeys,
            the L<sub>i</sub> and R<sub>i</sub> values as follows:
    </p><pre>    (C0,D0)=...
    (C1,D1)=...
    k1=...
    (C2,D2)=...
    k2=...
    ...
    (C16,D16)=...
    k16=...
    (L0,R0)=...
    (L1,R1)=...
    ...
    (L16,R16)=...</pre>
            The values of the C's, D's, L's, R's, and subkeys
            should be printed in hexstring format.  Please <b>only</b> output
            the L's and R's values during encryption of the
            <b>first 8-byte block</b>.
        </td>
    </tr><tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>decrypt</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">
            The output of this command is a binary file where each
            8-byte block is a direct DES decryption of the corresponding
            input 8-byte block.  If the original (binary) plaintext
            filesize is not a multiple of 8 bytes, the output of the
            decrypt command will not be the same as the plaintext file.
            <p>
            You must also output, to <tt>stderr</tt>, the values of the subkeys,
            the L<sub>i</sub> and R<sub>i</sub> values as follows:
    </p><pre>    (C0,D0)=...
    (C1,D1)=...
    k1=...
    (C2,D2)=...
    k2=...
    ...
    (C16,D16)=...
    k16=...
    (L0,R0)=...
    (L1,R1)=...
    ...
    (L16,R16)=...</pre>
            The values of the C's, D's, L's, R's, and subkeys
            should be printed in hexstring format.  Please <b>only</b> output
            the L's and R's values during decryption of the
            <b>first 8-byte block</b>.
        </td>
    </tr><tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>encrypt3</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">
            The output of this command is a binary file where each
            8-byte block is a direct 3DES encryption of the corresponding
            input 8-byte block.
        </td>
    </tr><tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>decrypt3</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">
            The output of this command is a binary file where each
            8-byte block is a direct 3DES decryption of the corresponding
            input 8-byte block.  If the original (binary) plaintext
            filesize is not a multiple of 8 bytes, the output of the
            decrypt command will not be the same as the plaintext file.
        </td>
    </tr>
</tbody></table>
</blockquote>

<p>

Please note that before encrypting or decrypting, your program
must make sure that the encryption key is valid and
call the <tt>tablecheck</tt> functionality internally to
make sure that you have a valid <tt>tablefile</tt> before proceeding.

</p><p>

Pleaes output reasonable and useful error messages if the command
is malformed or file does not exist or inaccessible.  If the key file
is malformed, please output meaningful error messages.
            </p></td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <!-- Section -->
        <tr><td colspan="3" align="LEFT" bgcolor="#000000" width="100%">
                <font color="#ffffff"><a name="format">
                <b><tt>tablefile</tt> Format</b></a></font>
            </td>
        </tr>
        <!-- Top Section -->
        <tr><td colspan="3" align="LEFT">
A <tt>tablefile</tt> is an ASCII file containing exactly 14 lines.
Each line has the format of <tt>key=value</tt> where <tt>key</tt>
can be one of the following (must be in uppercase):
<b><tt>IP</tt></b>,
<b><tt>E</tt></b>,
<b><tt>P</tt></b>,
<b><tt>S#</tt></b>,
<b><tt>V</tt></b>,
<b><tt>PC1</tt></b>, and
<b><tt>PC2</tt></b>, where <b><tt>#</tt></b> is a number between
1 and 8, inclusive.  To the right of the equal sign, <tt>value</tt> contains
a list of integer values that are separated by commas.
There should contain no white spaces (such as space or tab characters).
Each line corresponds to a DES internal table with the same name.
Please see the
<a href="http://merlot.usc.edu/cs531-s15/lectures.html#tentative">lecture slides on DES</a> or section
7.4 on pages 250-256 of the
<a href="http://www.cacr.math.uwaterloo.ca/hac/">
textbook (Handbook of Applied Cryptography)</a> (in Chapter 7)
for details.
The following are requirements for each of the tables (and corresponding
input lines).

<blockquote>
<table border="0" cellpadding="0" cellspacing="0">
    <tbody><tr><td align="LEFT" valign="TOP"><b>IP</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">This table contains a random permutation
                       of the values from 1 through 64, inclusive.
                       (You need to compute the inverse transform in your code.)
        </td>
    </tr>
    <tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>E</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">This table contains 48 values.  The allowed values are
                       between 1 through 32, inclusive.  All 32 numbers must
                       appear in this table at least once and at most twice.
        </td>
    </tr><tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>P</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">This table contains a random permutation
                       of the values from 1 through 32, inclusive.
        </td>
    </tr><tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>S#</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">This table contains 64 values, in a group of 16.
                       Each group is a random permutation
                       of the values from 0 through 15, inclusive.
        </td>
    </tr><tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>V</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">This table contains 16 values.
                       Each value can be either 1 or 2.
                       There should be 4 ones and 12 twos.
        </td>
    </tr><tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>PC1</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">This table contains 56 values.
                       These values are a random permutation
                       of the numbers from 1 through 64, inclusive,
                       with the values which are multiples of 8 removed.
        </td>
    </tr><tr><td>&nbsp;</td></tr>
    <tr><td align="LEFT" valign="TOP"><b>PC2</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">This table contains 48 values.
                       These values are a random permutation
                       of the numbers from 1 through 56, inclusive,
                       with 8 randomly chosen numbers removed.
        </td>
    </tr>
</tbody></table>
</blockquote>
            </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <!-- Section -->
        <tr><td colspan="3" align="LEFT" bgcolor="#000000" width="100%">
                <font color="#ffffff"><a name="testdata"><b>Test Data &amp; Sample Output</b></a>
                    </font>
            </td>
        </tr>
        <!-- Top Section -->
        <tr><td colspan="3" align="LEFT">
The <tt>tablefile</tt> for the standard DES is provided as
<a href="http://merlot.usc.edu/cs531-s15/homeworks/hw5/des.in"><tt>des.in</tt></a>.  Please compare it
against the following tables described in the lecture and textbook.

<blockquote>
    <img src="./Homework #5 - CSCI 531, Spring 2015_files/ip_e_p.png" border="0">
    <p>
    <img src="./Homework #5 - CSCI 531, Spring 2015_files/sbox.png" border="0">
    </p><p>
    <img src="./Homework #5 - CSCI 531, Spring 2015_files/pc12.png" border="0">
</p></blockquote>


<p>

The standard DES
test vectors is also provided as <a href="http://merlot.usc.edu/cs531-s15/homeworks/hw5/testvec.in">testvec.in</a>.
The first 8 bytes of <tt>testvec.in</tt> is used below and provided as
<a href="http://merlot.usc.edu/cs531-s15/homeworks/hw5/short.in">short.in</a>".

</p><p>

For the <tt>"encrypt -k=0123456789abcdef -t=des.in
<a href="http://merlot.usc.edu/cs531-s15/homeworks/hw5/short.in">short.in</a>"</tt> command,
during key scheduling, your program should output the following
to <tt>stderr</tt>:
    </p><pre>    (C0,D0)=f0ccaa0aaccf00
    (C1,D1)=e1995415599e01
    k1=0b02679b49a5
    (C2,D2)=c332a83ab33c02
    k2=69a659256a26
    (C3,D3)=0ccaa0faccf00a
    k3=45d48ab428d2
    (C4,D4)=332a83cb33c02a
    k4=7289d2a58257
    (C5,D5)=ccaa0f0ccf00aa
    k5=3ce80317a6c2
    (C6,D6)=32a83c333c02ab
    k6=23251e3c8545
    (C7,D7)=caa0f0ccf00aac
    k7=6c04950ae4c6
    (C8,D8)=2a83c333c02ab3
    k8=5788386ce581
    (C9,D9)=55078667805566
    k9=c0c9e926b839
    (C10,D10)=541e199e015599
    k10=91e307631d72
    (C11,D11)=50786658055667
    k11=211f830d893a
    (C12,D12)=41e1995015599e
    k12=7130e5455c54
    (C13,D13)=07866550556678
    k13=91c4d04980fc
    (C14,D14)=1e1995415599e0
    k14=5443b681dc8d
    (C15,D15)=78665505566780
    k15=b691050a16b5
    (C16,D16)=f0ccaa0aaccf00
    k16=ca3d03b87032</pre>

During encryption of your program should output the following
to <tt>stderr</tt>:
    <pre>    (L0,R0)=b7a4873600fe1327
    (L1,R1)=00fe1327c9efe379
    (L2,R2)=c9efe379c225d717
    (L3,R3)=c225d7171efc7384
    (L4,R4)=1efc738476f2b3de
    (L5,R5)=76f2b3de10d55380
    (L6,R6)=10d55380e90739fd
    (L7,R7)=e90739fd572337f0
    (L8,R8)=572337f0cd9968e4
    (L9,R9)=cd9968e4256a96b9
    (L10,R10)=256a96b98049c24c
    (L11,R11)=8049c24ca1663aa6
    (L12,R12)=a1663aa6b714e099
    (L13,R13)=b714e099a3eb2c46
    (L14,R14)=a3eb2c46b94da965
    (L15,R15)=b94da9651a037d0d
    (L16,R16)=1a037d0d6091a7a1</pre>

The output of your program, in hexstring representation, should be:
    <pre>    3fa40e8a984d4815</pre>

This result matches the textbook.
            </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <!-- Section -->
        <tr><td colspan="3" align="LEFT" bgcolor="#000000" width="100%">
                <font color="#ffffff"><a name="grading"><b>Grading Guidelines</b></a>
                    </font>
            </td>
        </tr>
        <!-- Top Section -->
        <tr><td colspan="3" align="LEFT">
<!--
The grading guidelines is not available yet.
  -->

The <a href="http://merlot.usc.edu/cs531-s15/homeworks/hw5/hw5-grading.txt">grading guidelines</a> has been made available.
Please run the scripts in the guidelines on <tt>nunki.usc.edu</tt>.

<p>     
        
The grading guidelines is the <b>only</b> grading procedure we will use to
grade your program.  No other grading procedure will be used.
To the best of our effort, we will only change the testing data for
grading but not the commands.  (We may make minor changes if we discover
bugs in the script or things that we forgot to test.)  It is strongly
recommended that you run your code through the scripts in the grading guidelines.
            </p></td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <!-- Section -->
        <tr><td colspan="3" align="LEFT" bgcolor="#000000" width="100%">
                <font color="#ffffff"><a name="misc"><b>Miscellaneous Requirements and Hints</b></a>
                    </font>
            </td>
        </tr>
        <!-- Top Section -->
        <tr><td colspan="3" align="LEFT">
<ul>
<li>Just want to emphasize that for this assignment,
    you are <b>not</b> allowed to use publicly available DES-specific
    code.  Generic public code for other purpose, such as parsing input data,
    is allowed.
<p>
</p></li><li>Although there is no memory buffer size limit for this assignment, when
    reading an input file for encryption/decryption, please use a reasonable
    size file buffer.
<p>
</p></li><li>It's important that <b>every byte</b> of your data is read and written
    correctly.  You will <b>lose a lot of points</b> if one byte of data is
    generated incorrectly!  The grading of this assignment will be <b>harsh</b>.
<p>
</p></li><li>Please follow the UNIX convention that, when your output is an ASCII
    file, append '\n' in the last line of the output if it's not a
    blank line.  (This way, you don't get the commandline prompt appearing at
    the wrong place on the screen.)
<p>
</p></li><li>String I/O functions such as <tt>fgets()</tt>, <tt>scanf()</tt>, and
    <tt>printf()</tt> are really meant for inputing/outputing
    null-terminated <i>strings</i>.
    Do <b>not</b> use them to input/output binary data!
<p>
</p></li><li>The Solaris workstations in the ISD lab in SAL have the same
    setup as nunki.usc.edu.  So, if you are logged on to one of
    these workstations, please do your development locally and
    not to overload nunki unnecessarily.
<p>
</p></li><li>Start working on this <b>early</b>!  Please don't complain
    to the instructor that this assignment is too tedious or
    it takes too much work just to parse the commandline.
    Get it done early and get it done right!
<p>
</p></li><li>Hints on parsing a <tt>tablefile</tt>
    <a href="http://merlot.usc.edu/cs531-s15/homeworks/hw5/parsing.html">has been made available</a>.
</li></ul>
            </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <!-- Section -->
        <tr><td colspan="3" align="LEFT" bgcolor="#000000" width="100%">
                <font color="#ffffff"><a name="submit"><b>Submission</b></a></font>
            </td>
        </tr>
        <!-- Top Section -->
        <tr><td colspan="3" align="LEFT">
All assignments are to be submitted electronically - including
your README file. To submit your work, you must first
<tt>tar</tt> all the files you want to submit into a <b>tarball</b> and
<tt>gzip</tt> it to create a <b>gzipped tarfile</b> named
<tt><b>hw5.tar.gz</b></tt>.  Then you upload
<tt><b>hw5.tar.gz</b></tt> to the
<a href="http://merlot.usc.edu/cs531-s15/bsubmit.html">Bistro</a> system.
On <tt>nunki.usc.edu</tt> or <tt>aludra.usc.edu</tt>,
the command you can use to create a gzipped tarfile is:

    <pre>    /usr/usc/bin/gtar cvzf hw5.tar.gz MYFILES</pre>

Where <b><tt>MYFILES</tt></b> is the list of file names that you are submitting
(you can also use wildcard characters if you are sure that it will pick up only
the right files).
<b>DO NOT</b> submit your compiled code, just your source code and
README file.  <b>Two point will be deducted</b> if you submit extra
binary files, such as <tt>hw5</tt>, <tt>.o</tt>,
<tt>core</tt>, or files that can be <b>generated</b> from the rest of your submission.

<p>
Please note that the 2nd commandline argument of the <tt>gtar</tt> command above
is the <b>output</b> filename of the <tt>gtar</tt> command.  So, if you omit
<tt>hw5.tar.gz</tt> above, you may accidentally replace one of your files with
the output of the <tt>gtar</tt> command.  So, please make sure that the
first commandline argument is <tt><b>cvzf</b></tt> and the 2nd commandline argument
is <tt><b>hw5.tar.gz</b></tt>.

</p><p>
In your README file, you should include the command that the grader
should use to compile your code to generate <b><tt>hw5</tt></b>.
If you don't include such instruction, the grader will assume that the command
specified in the spec should be used to compile your code.
But if they can't get your code to compile easily and you don't submit
compilation instructions, you will lose points.  Please also note that
you MUST include a README file in your submission.  If you have nothing
to put inside the README file, please write "(This file intentionally left blank.)"
in your README file.

</p><p>
Here are a couple of sample commands for creating your <tt>hw5.tar.gz</tt> file
(your command will vary depending on what files you want to submit):
    </p><pre>    /usr/usc/bin/gtar cvzf hw5.tar.gz *.c *.h Makefile README
    /usr/usc/bin/gtar cvzf hw5.tar.gz *.cpp *.h Makefile README.txt</pre>

You should read the output of the above commands carefully to make sure
that <tt>hw5.tar.gz</tt> is created properly.
If you don't understand the output of the above commands, you need to learn
how to read it!  It's your responsibility to ensure that
<tt>hw5.tar.gz</tt> is created properly.

<p>
You need to run <a href="http://merlot.usc.edu/cs531-s15/bsubmit.html"><b><tt>bsubmit</tt></b></a> to
submit hw5.tar.gz to the submission server.
Please use the following command:
    </p><pre><b>
    ~csci551b/bin/bsubmit upload \
        -email `whoami`@usc.edu \
        -event merlot.usc.edu_80_1372906710_65 \
        -file hw5.tar.gz</b></pre>

Please note that the quotation marks surrounding <tt>whoami</tt> are
<b>back-quote</b> characters and not single quotes.  It's best if
you just copy and paste the above command into your console and not
try to type the whole command in.

<p>

If the command is executed successfully, the output should look like the
<a href="http://merlot.usc.edu/cs531-s15/bsubmit.html#normal">sample mentioned in the submission web page</a>.
If it doesn't look like that, please fix your command and rerun it until it looks
right.  If there are problems, please contact the instructor.

</p><p>
It is extreme important that you also <a href="http://merlot.usc.edu/cs531-s15/submit.html#verify"><b>verify your submission</b></a>
after you have submitted <tt>hw5.tar.gz</tt> electronically to make
sure that everything you have submitted is everything you wanted us to grade.

</p><p>
Finally, please be familiar with the <a href="http://merlot.usc.edu/cs531-s15/submit.html">Electronic Submission Guidelines</a>
and information on the <a href="http://merlot.usc.edu/cs531-s15/bsubmit.html">bsubmit web page</a>.
            </p></td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        </tbody></table>
    </td>
</tr>
</tbody></table>

<hr>
[<i>Last updated Tue Mar 24 2015</i>] &nbsp;&nbsp;
[<i>Please see <a href="http://merlot.usc.edu/cs531-s15/copyright.html">copyright</a> regarding copying.</i>]

<!-- @(#)$Id: index.html,v 1.3 2015/03/24 20:09:43 william Exp $ -->



</body></html>
'''
