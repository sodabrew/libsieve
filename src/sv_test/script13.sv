require ["relational", "fileinto"];
# Using this message:

#      received: ...
#      received: ...
#      subject: example
#      to: foo@example.com, baz@example.com
#      cc: qux@example.com

# The test:

      if address :count "ge" :comparator "i;ascii-numeric"
                      ["to", "cc"] ["3"] {
	fileinto "Address test correct.";
	}

#   would evaluate to true and the test

     elsif anyof ( address :count "ge" :comparator "i;ascii-numeric"
                      ["to"] ["3"],
              address :count "ge" :comparator "i;ascii-numeric"
                      ["cc"] ["3"] ) {
	fileinto "Anyof Address test incorrect.";
	}

#   would evaluate to false.

#   To check the number of received fields in the header, the following
#   test may be used:

      header :count "ge" :comparator "i;ascii-numeric"
                      ["received"] ["3"]

#   This would evaluate to false.  But

      header :count "ge" :comparator "i;ascii-numeric"
                      ["received", "subject"] ["3"]

#   would evaluate to true.

#   The test:

      header :count "ge" :comparator "i;ascii-numeric"
                      ["to", "cc"] ["3"]

#   will always evaluate to false on an RFC 2822 compliant message
#   [RFC2822], since a message can have at most one "to" field and at
#   most one "cc" field.  This test counts the number of fields, not the
#   number of addresses.




