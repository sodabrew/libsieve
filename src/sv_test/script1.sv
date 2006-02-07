    if header :contains ["From"]  ["coyote"] {
        redirect "acm@frobnitzm.edu";
    } elsif header :contains "Subject" "$$$" {
        redirect "postmaster@frobnitzm.edu";
    } else {
        redirect "field@frobnitzm.edu";
    }

