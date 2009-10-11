require ["fileinto", "reject", "vacation"];
if header :contains ["From"] "myaddress@gmail.com" {
   vacation "Out of the office.";
   stop;
}

