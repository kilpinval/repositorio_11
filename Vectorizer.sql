-- Vectorizer using OpenAI text-embedding-3-small
SELECT ai.create_vectorizer(
  'public.blogs'::regclass,
  destination => 'blogs_embedding_small',
  embedding => ai.embedding_openai('text-embedding-3-small', 1536),
  chunking => ai.chunking_recursive_character_text_splitter('content'),
  formatting => ai.formatting
)
SELECT ai.create_vectorizer(
  'blog'::regclass,
  destination => 'blog_contents_embeddings',
  embedding => ai.embedding_openai('text-embeddig-3-small',768),
  chunking => ai.chunking_recursive_character_text_splitter('contents', chunk_size => 700),
  formatting => ai.formatting_python_template('$title - by $author - $chunk'),
  indexing => ai.indexing_hnsw(min_rows => 100000, opclass => 'vector_12_ops')
);
  
