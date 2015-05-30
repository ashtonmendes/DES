<html><head><meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<title>Homework #5 - CSCI 531, Spring 2015</title>
<link href="./Homework #5 - CSCI 531, Spring 2015_files/cs531bc.css" rel="stylesheet" type="text/css">
<link rev="made" href="mailto:bill.cheng@acm.org"><style type="text/css"></style></head>
<body bgcolor="#FFFFFF" link="#D02090" vlink="#996600" alink="#990000">

The purpose of this assignment is to get familiar with
DES by implementing DES from scratch with the flexibility
of changing some of the internal tables.

</tr>
<tr><td>&nbsp;</td></tr>
<!-- Section -->
<tr><td colspan="3" align="LEFT" bgcolor="#000000" width="100%">
        <font color="#ffffff"><a name="compile"><b>Compiling</b></a></font>
    </td>
</tr>
<!-- Top Section -->
<tr><td colspan="3" align="LEFT">
<pre>    make hw5</pre>
an executable named <b>hw5</b> is created.

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
Follows the UNIX convention that <b>commandline options</b>
can come in any order.  (Note: a <b>commandline option</b> is a
commandline argument that begins with a <b>-</b> character in a
commandline syntax specification.)
If an input file is not specified, the program
reads from <tt>stdin</tt>.
Output of the program goes to <tt>stdout</tt> and
error messages go to <tt>stderr</tt>.

</p><p>

The meaning of the commands are:

</p><blockquote>
<table border="0" cellpadding="0" cellspacing="0">
    <tbody><tr><td align="LEFT" valign="TOP"><b>tablecheck</b></td>
        <td valign="TOP">&nbsp;&nbsp;:&nbsp;&nbsp;</td>
        <td valign="TOP">Check the integrity of <tt>tablefile</tt>.
                       Please see tablefile format
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
                       8 bytes, pads it with zeroes.
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
                       8 bytes, pads it with zeroes.
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
                       8 bytes, pads it with zeroes.
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
                       8 bytes, pads it with zeroes.
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
            The command produces no output in <tt>stdout</tt>.
            All error output goes to <tt>stderr</tt>.
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
            To <tt>stderr</tt>, the values of the subkeys,
            the L<sub>i</sub> and R<sub>i</sub> values are output as follows:
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
            are printed in hexstring format.  The L's and R's values during encryption of the
            <b>first 8-byte block</b> are output.
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
            To <tt>stderr</tt>, the values of the subkeys,
            the L<sub>i</sub> and R<sub>i</sub> values are output as follows:
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
            are printed in hexstring format.  The L's and R's values during decryption of the
            <b>first 8-byte block</b> are output. 
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

</p><p>
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

</body></html>
