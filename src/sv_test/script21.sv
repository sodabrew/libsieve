require "fileinto";

if allof (header :contains "From" "fazj@barshop.com", 
	header :contains "X-Spam-Folder" "YES") {
        fileinto "Spam";
}
elsif allof (header :contains "Received" "foo_root@slv.net", 
	header :contains "X-Spam-Folder" "YES") {
        fileinto "Spam";
}
else {
        fileinto "INBOX";
}
