
require ["fileinto", "comparator-i;ascii-numeric"];

if header :value "gt" :comparator "i;ascii-numeric"  "X-Spam-score" "1" {
  fileinto "gt";
} 
if header :value "ge" :comparator "i;ascii-numeric"  "X-Spam-score" "10" {
  fileinto "ge";
} 
if header :value "lt" :comparator "i;ascii-numeric"  "X-Spam-score" "30" {
  fileinto "lt";
} 
if header :value "le" :comparator "i;ascii-numeric"  "X-Spam-score" "25" {
  fileinto "le";
} 
if header :value "eq" :comparator "i;ascii-numeric"  "X-Spam-score" "25" {
  fileinto "eq";
} 
if header :value "ne" :comparator "i;ascii-numeric"  "X-Spam-score" ["1000", "20"] {
  fileinto "ne";
}

if header :value "gt" :comparator "i;ascii-numeric"  "X-Spam-score" "25" {
  fileinto "Fail: gt";
} 
if header :value "ge" :comparator "i;ascii-numeric"  "X-Spam-score" "26" {
  fileinto "Fail: ge";
} 
if header :value "lt" :comparator "i;ascii-numeric"  "X-Spam-score" "25" {
  fileinto "Fail: lt";
} 
if header :value "le" :comparator "i;ascii-numeric"  "X-Spam-score" "24" {
  fileinto "Fail: le";
} 
if header :value "eq" :comparator "i;ascii-numeric"  "X-Spam-score" "2.5" {
  fileinto "Fail: eq";
} 
if header :value "ne" :comparator "i;ascii-numeric"  "X-Spam-score" "25.64" {
  fileinto "Fail: ne";
}
