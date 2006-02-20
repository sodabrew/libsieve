require ["fileinto", "subaddress"];

if envelope :detail "to" "AllowedBox" {
        fileinto "AllowedBox";
}
