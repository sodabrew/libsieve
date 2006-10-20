require ["fileinto"];

if allof (address :contains ["From"] "Alexandru") {
        fileinto "Junk Mail";
	}
