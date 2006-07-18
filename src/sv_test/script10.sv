require "imap4flags";

setflag "\\Deleted";

addflag "\\Foo";
addflag "\\Foo";
addflag "\\Bar";

removeflag "\\Foo";
removeflag "\\Qux";
removeflag ["\\Bar", "\\Deleted"];
removeflag "\\Deleted";

addflag "\\Qux";

if hasflag "\\Qux" {
    addflag "\\HasQux";
}

if not hasflag "\\Not" {
    addflag "\\NoNot";
}

keep;
