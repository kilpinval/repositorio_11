-- Vectorizer using OpenAI text-embedding-3-small
SELECT ai.create_vectorizer(
  'public.blogs'::regclass,
  destination => 'blogs_embedding_small',
  embedding => ai.embedding_openai('text-embedding-3-small', 1536),
  chunking => ai.chunking_recursive_character_text_splitter('content'),
  formatting => ai.formatting
)
