require ["fileinto", "subaddress", "imap4flags"];

if envelope :detail "to" "AllowedBox" {
        fileinto :flags ["\\Flagged", "\\Deleted", "3", "4", "5", "6", "7", "8", "9", "10"]
		"AllowedBox";
        fileinto :flags ["\\Flagged", "12", "13", "14", "15"]
		"AllowedBox";
        fileinto :flags "" "AllowedBox";
	fileinto "MooBox";
        keep :flags ["\\Keep"];
}
