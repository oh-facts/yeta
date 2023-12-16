import sys


ast_expressions = [

    {"type": "table", "fields": ["", "Token operator", "Expr right"]},
    {"type": "Grouping", "fields": ["Expr expression"]},
    {"type": "Literal", "fields": ["Object value"]},
    {"type": "Unary", "fields": ["Token operator", "Expr right"]}
]

def main():
    if len(sys.argv) != 2:
        print("Usage: generate_ast <output directory>")
        sys.exit(69)

    output_dir = sys.argv[1]

    print("Files generated at " + sys.argv[1]);

if __name__ == "__main__":
    main()