require ["fileinto", "relational"];

if header :value "gt" :comparator "i;ascii-casemap" "Greater" "Bob" {
    fileinto "gt";
}
if header :value "ge" :comparator "i;ascii-casemap" "Greater-equal" "Bob" {
    fileinto "ge";
}
if header :value "lt" :comparator "i;ascii-casemap" "less" "Bob" {
    fileinto "lt";
}
if header :value "le" :comparator "i;ascii-casemap" "less-Equal" "Bob" {
    fileinto "le";
}
if header :value "ne" :comparator "i;ascii-casemap" "Not-Equal" "Bob" {
    fileinto "ne";
}
if header :value "eq" :comparator "i;ascii-casemap" "EQUAL" "Bob" {
    fileinto "eq";
}

