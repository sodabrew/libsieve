require ["fileinto"];

if allof (address :contains ["From"] "envelope@example.org") {
# if allof (header :contains ["List-ID"] "<ubuntu-users.lists.ubuntu.com>") {
        fileinto "Listen/Ubuntu/Users";
} else {
	fileinto "NotUnbuntu";
}

