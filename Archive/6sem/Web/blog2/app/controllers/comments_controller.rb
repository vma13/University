class CommentsController < ApplicationController
  
  def create
    @post = Post.find(params[:post_id])
    @comment = @post.comments.create(params[:comment])
    redirect_to post_path(@post)
  end
  
  def edit
    @post = Post.find(params[:post_id])
    if logged_in?
      @comment = @post.comments.find(params[:id])
      @comment.status = true
      @comment.save
      redirect_to(@post, :notice => 'Комментарий одобрен.')
    end
    redirect_to(@post, :notice => 'Комментарий не одобрен.')
  end
  
end
