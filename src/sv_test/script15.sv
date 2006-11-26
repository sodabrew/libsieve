
require ["envelope", "fileinto", "relational"];

     if envelope :count "gt" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "gt";
} elsif header   :count "ge" :comparator "i;ascii-numeric"  "from" ["1", "2"] {
    fileinto "ge";
} elsif envelope :count "lt" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "lt";
} elsif envelope :count "le" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "le";
} elsif envelope :count "eq" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "eq";
} elsif envelope :count "ne" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "ne";
}

     if envelope :value "gt" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "gt";
} elsif header   :value "ge" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "ge";
} elsif envelope :value "lt" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "lt";
} elsif envelope :value "le" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "le";
} elsif envelope :value "eq" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "eq";
} elsif envelope :value "ne" :comparator "i;ascii-numeric"  "from" "1" {
    fileinto "ne";
}
