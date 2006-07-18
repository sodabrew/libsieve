require ["imap4flags"];

if header :contains ["From"]  ["coyote"] {
    redirect "acm@frobnitzm.edu";
} elsif header :contains "Subject" "$$$" {
    keep :flags "\\Flagged";
} else {
    redirect "field@frobnitzm.edu";
}


