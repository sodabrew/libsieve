	require "fileinto";

	/** Hello, I am a comment!! ****/ /** /* */

	if header :is "X-Mailinglist" "suse-linux" { 	
		fileinto "INBOX.Listen.suse-linux";} 	
	elsif header :contains "Mailing-List" "reiserfs" {
		fileinto "INBOX.Listen.reiserfs";}
	elsif address :contains :all ["to", "cc", "bcc"] "free-clim" {
		fileinto "INBOX.Listen.free-clim";}
	elsif header :contains "List-Id" "gnupg-users.gnupg.org" { 
		fileinto "INBOX.Listen.gnupg";}
	elsif header :is "X-loop" "isdn4linux" {
		fileinto "INBOX.Listen.isdn4linux";}
	elsif header :contains  "Mailing-list" "qmail-help@list.cr.yp.to"{
		fileinto "INBOX.Listen.qmail";}
	elsif allof (header :contains "Sender" "owner-info-cyrus@list",
			address :contains :localpart ["to", "cc", "bcc"] "info-cyrus"){
		fileinto "INBOX.Listen.info-cyrus";}
	elsif header :contains "Sender" "ntbugtraq@listserv"{
		fileinto "INBOX.Listen.ntbugtraq";}
	elsif header :is "list-id" "<ietf-mta-filters.imc.org>"{
		fileinto "INBOX.Listen.sieve";}
	elsif header :contains "From" "securityportal-l@listserv.securityportal.com"{
		fileinto "INBOX.Newsletter.securityportal";}
	elsif address :contains :all ["from"] "newsletter@ebay"{
		fileinto "INBOX.Newsletter.ebay";} 
	elsif address :contains :all ["to", "cc", "bcc"] "allegro-cl@cs.berkeley.edu"{
		fileinto "INBOX.Listen.allegro-cl";}
	elsif address :contains :all ["to", "cc", "bcc"] "plob@lisp.de"{
		fileinto "INBOX.Listen.plob";}		 
	else {
		fileinto "INBOX";}

