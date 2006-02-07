require ["imapflags"];

if header :contains ["From"]  ["coyote"] {
    redirect "acm@frobnitzm.edu";
} elsif header :contains "Subject" "$$$" {
    mark;
} else {
    redirect "field@frobnitzm.edu";
}


