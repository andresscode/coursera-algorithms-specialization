import java.io.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;

public class Solution {

    private FastScanner in;
    private PrintWriter out;
    // store all strings in one list
    private List<List<String>> elems;
    // for hash function
    private int bucketCount;
    private int prime = 1000000007;
    private int multiplier = 263;

    public static void main(String[] args) throws IOException {
        new Solution().processQueries();
    }

    private int hashFunc(String s) {
        long hash = 0;
        for (int i = s.length() - 1; i >= 0; --i)
            hash = (hash * multiplier + s.charAt(i)) % prime;
        return (int)hash % bucketCount;
    }

    private Query readQuery() throws IOException {
        String type = in.next();
        if (!type.equals("check")) {
            String s = in.next();
            return new Query(type, s);
        } else {
            int ind = in.nextInt();
            return new Query(type, ind);
        }
    }

    private void writeSearchResult(boolean wasFound) {
        out.println(wasFound ? "yes" : "no");
        // Uncomment the following if you want to play with the program interactively.
        // out.flush();
    }

    private void processQuery(Query query) {
        //@log out.println(String.format("query=%s", query.type));
        if ("check".equals(query.type)) {
          for (int i = elems.get(query.ind).size()-1; i >= 0; --i)
            out.print(elems.get(query.ind).get(i) + " ");
          out.println();
        } else {
          int hash = hashFunc(query.s);
          //@log out.println("query=" + query.s + ", hash=" + hash);
          switch (query.type) {
            case "add":
                if (!elems.get(hash).contains(query.s))
                    elems.get(hash).add(query.s);
                break;
            case "del":
                if (elems.get(hash).contains(query.s))
                    elems.get(hash).remove(query.s);
                break;
            case "find":
                writeSearchResult(elems.get(hash).contains(query.s));
                break;
            default:
                throw new RuntimeException("Unknown query: " + query.type);

          }
        }
    }

    public void processQueries() throws IOException {
        in = new FastScanner();
        out = new PrintWriter(new BufferedOutputStream(System.out));
        bucketCount = in.nextInt();
        elems = new ArrayList<>();
        for (int i = 0; i < bucketCount; ++i)
          elems.add(new ArrayList<>());
        int queryCount = in.nextInt();
        for (int i = 0; i < queryCount; ++i) {
            processQuery(readQuery());
        }
        out.close();
    }

    static class Query {
        String type;
        String s;
        int ind;

        public Query(String type, String s) {
            this.type = type;
            this.s = s;
        }

        public Query(String type, int ind) {
            this.type = type;
            this.ind = ind;
        }
    }

    static class FastScanner {
        private BufferedReader reader;
        private StringTokenizer tokenizer;

        public FastScanner() {
            reader = new BufferedReader(new InputStreamReader(System.in));
            tokenizer = null;
        }

        public String next() throws IOException {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                tokenizer = new StringTokenizer(reader.readLine());
            }
            return tokenizer.nextToken();
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }
}
