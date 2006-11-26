
# Note that this is a MUST and should be tested:
#
#   An implementation MUST ensure that the test for envelope "to" only
#   reflects the delivery to the current user.  It MUST not be possible
#   for a user to determine if this message was delivered to someone else
#   using this test.

# RFC 3431bis Extended Example

      require ["relational", "fileinto", "comparator-i;ascii-numeric"];

      if header :value "lt" :comparator "i;ascii-numeric"
                ["x-priority"] ["3"]
      {
         fileinto "Priority";
      }

      elsif address :count "gt" :comparator "i;ascii-numeric"
                 ["to"] ["5"]
      {
         # everything with more than 5 recipients in the "to" field
         # is considered SPAM
         fileinto "SPAM";
      }

      elsif address :value "gt" :all :comparator "i;ascii-casemap"
                 ["from"] ["M"]
      {
         fileinto "From N-Z";
      }
      
      else {
         fileinto "From A-M";
      }

      if allof ( address :count "eq" :comparator "i;ascii-numeric"
                         ["to", "cc"] ["1"] ,
                 address :all :comparator "i;ascii-casemap"
                         ["to", "cc"] ["me@foo.example.com"] )
      {
         fileinto "Only me";
      }

