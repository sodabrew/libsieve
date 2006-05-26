require ["fileinto"];

if allof (header :contains "List-Id" "<ubuntu-users.lists.ubuntu.com>") {
        fileinto "Listen/Ubuntu/Users";
}

fileinto "NotUnbuntu";
