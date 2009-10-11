require ["fileinto", "enotify", "imap4flags", "reject"];

reject "Nothing";
#keep;

setflag "\Initial";

# poop;

if header :contains "X-Foo" "one" {
	fileinto "one.one";
	fileinto "one.two";
	fileinto "one.three";
	fileinto "one.four";
	fileinto "one.five";
	stop;
} elsif header :contains "X-Foo" "foo" {
	notify :message "two.one" "mailto:test@localhost";
	notify :message "two.two" "mailto:test@localhost";
	notify :message "two.three" "mailto:test@localhost";
	notify :message "two.four" "mailto:test@localhost";
	notify :message "two.five" "mailto:test@localhost";
	notify :message "two.six" "mailto:test@localhost";
	if header :contains "X-Two" "two" {
		fileinto "two.foo.two";
	}
} else {
	keep :flags "\Nuts";
	keep :flags "\Again";
}

setflag "\Final";

if header :contains "X-Foo" "x" {
} else {
}

# keep;
